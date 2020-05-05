{-# LANGUAGE GeneralizedNewtypeDeriving #-}
{-# LANGUAGE UndecidableInstances #-}
{-# LANGUAGE MultiParamTypeClasses #-}
{-# LANGUAGE FunctionalDependencies #-}
{-# LANGUAGE FlexibleInstances #-}
module Test
  ( Test, TestCase (..), TestData, emptyTD
  , assertVal, testCond, testVal, testString, testOne, tests, test
  , runTest, evalTest, execTest
  ) where

import Control.Applicative
import qualified Control.Monad.Trans.State.Lazy as S
import Control.Monad.IO.Class

class (Monad m) => MonadState s m | m -> s where
  get :: m s
  put :: s -> m ()

instance (Monad m) => MonadState s (S.StateT s m) where
  get = S.get
  put = S.put

modify :: MonadState s m => (s -> s) -> m ()
modify f = do
  s <- get
  put (f s)

runStateT = S.runStateT

newtype Test d a = MkTest { getTestState :: S.StateT (TestData d) IO a }
  -- The Holy Trinity + MonadState + MonadIO
  deriving (Functor, Applicative, Monad, MonadState (TestData d), MonadIO)

data TestCase a = TestCase
  { testName    :: String
  , testData    :: a
  , testError :: String
  , testPassed  :: IO Bool
  , testResult  :: a
  }

type TestData a = [TestCase a]

emptyTD :: TestData a
emptyTD = []

{- Assertion primitives
  s : the String to display
  d : points
  b : boolean that indicates test value
  p : property function
  x : value to check
-}
assertValIO :: String -> d -> String -> IO Bool -> Test d ()
assertValIO s d e b = modify $ \ tcs -> tcs ++ [TestCase s d e b d]

assertVal s d b = assertValIO s d "" (return b)

tests
  :: Fractional b =>
     Int -> b -> [([Char], b, String, IO Bool)] -> Test b ()
tests ex points testList = sequence_ $ map tt testList
      where
        total = foldl (+) 0 $ map (\(_, p, _, _) -> p) testList
        tt (s, d, e, b) = assertValIO ("[" ++ (show ex) ++ "] " ++ s) (points * d / total) e b

testOne ex (s, d, e, b) = assertValIO ("[" ++ (show ex) ++ "] " ++ s) d e b

test s d e b = (s, d, e, b)

testCond s d b = test s d "boolean test failed" $ return b

testVal s d ve vg = test s d err $ return $ vg == ve
  where err = ("given value " ++ show vg ++ " not equal to expected value " ++ show ve)

testString s d ve vg = test s d err $ return $ vg == ve
  where err = ("given value " ++ vg ++ " not equal to expected value " ++ ve)

-- State-style de-lifting functions
runTest :: Test d a -> TestData d -> IO (a, TestData d)
runTest t = runStateT $ getTestState t

evalTest :: Test d a -> TestData d -> IO a
evalTest t = fmap fst . runTest t

execTest :: Test d a -> TestData d -> IO (TestData d)
execTest t = fmap snd . runTest t
