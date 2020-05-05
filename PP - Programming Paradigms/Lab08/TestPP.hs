{-# LANGUAGE GeneralizedNewtypeDeriving #-}
{-# LANGUAGE UndecidableInstances #-}
{-# LANGUAGE MultiParamTypeClasses #-}
{-# LANGUAGE FunctionalDependencies #-}
{-# LANGUAGE FlexibleInstances #-}

module TestPP 
  ( quickCheck, vmCheck
  , testCond, testVal, testManually, testSet, test, tests
  , TestData, TestCase
  ) where

import qualified Control.Exception as E (catch, evaluate, SomeException (..))
import Data.List
import Debug.Trace

{- Defines one test case, internally.
-}
data TestCase = TestCase
  { testIndex :: Integer  -- the number of the excercise
  , testDescr   :: String -- description of the test
  , testPoints  :: Float  -- points for the test case
  , testError :: String -- error if the test failed
  , testPassed  :: Bool   -- has passed? also lazily contains the actual test
  }

{-Information for testing an entire exercise (is a list of test cases).
-}
newtype TestData = TD {getTestCases :: [TestCase]}

{- Printing a test also checks it -}
instance Show TestData where
  show = concat . intersperse "\n" . map (testMessage . testResult) . getTestCases

{- Contains information obtained from running one test case.
-}
data TestCaseResult = TestCaseResult
  { testExercise       :: Integer     -- the number of the exercise
  , testMessage        :: String      -- full output of the test
  , testScore        :: Float     -- how much the test actually scored
  , testSubjectUndefined   :: Bool      -- was the exercise undefined?
  , testExcepted       :: Bool      -- has the test resulted in an exception?
  } deriving Show

{- Builds test data for an exercise, based on the descriptions of test cases -}
tests :: Integer -> Float -> [TestCase] -> TestData
tests ex points testList = TD $ map tt testList
      where
        total = foldl (+) 0 $ map (\(TestCase _ _ p _ _) -> p) testList
        tt (TestCase _ d p e b) = TestCase ex d (points * p / total) e b

-- use to insert one single test for an exercise
test :: Integer -> TestCase -> TestData
test ex (TestCase _ d p e b) = TD [TestCase ex d p e b]

{- Builds the description of a a test case. The value is a boolean.
  The points represent the fraction of the total points of the exercise.
  For the moment the exercise number is unknown
-}
buildTest :: String -> Float -> String -> Bool -> TestCase
buildTest = TestCase 0

{- Describes a test case which evaluates a boolean value. -}
testCond :: String -> Float -> Bool -> TestCase
testCond descr points bool = buildTest descr points "boolean test failed" bool

{- Describes a test case which evaluates the equality of two values (expected and given). -}
testVal :: (Show a, Eq a) => String -> Float -> a -> a -> TestCase
testVal descr points ve vg = testWith descr "value" "equal" points ve (==) vg

{- Describes a test case which evaluates the equality of two sets (expected and given). -}
testSet :: (Show a, Eq a) => String -> Float -> [a] -> [a] -> TestCase
testSet descr points vg ve = testWith descr "set" "same" points ve sameElements vg

{- Describes a test case which compares an expected and a given value based on a function (op). vname and opname describe what the values are and what the comparator represents. -}
testWith :: (Show a1, Show a) => String -> String -> String -> Float
     -> a -> (a -> a1 -> Bool) -> a1 -> TestCase
testWith descr vname opname points ve op vg = buildTest descr points err (ve `op` vg)
  where err = ("given " ++ vname ++ " " ++ show vg ++ " not " ++ opname ++ " to expected " ++ vname ++ " " ++ show ve)

{- Describes a testCase which must be tested manually. The result of the manual check must be given as first argument. -}
testManually :: String -> Float -> Bool -> TestCase
testManually descr points bool = buildTest ("MANUAL Check for " ++ descr) points
      "manual test not validated" bool

{- tests if two sets are identical -}
sameElements :: (Eq a) => [a] -> [a] -> Bool
sameElements xs ys = null (xs \\ ys) && null (ys \\ xs)

{- builds a TestCaseResult based on a TestCase -}
testResult :: TestCase -> TestCaseResult
testResult tc = TestCaseResult (testIndex tc)
                ("[" ++ show (testIndex tc) ++ "]" ++ (if tp then "[OK] " else "[--] ")
                  ++ testDescr tc ++ ": " ++
                  putResult tp (testPoints tc) (testError tc))
                (if tp then testPoints tc else 0)
                False False
  where
    tp = testPassed tc
    putResult p d e = if p then "+" ++ (show d) ++ " PASSED" else "FAILED: " ++ e
            

{- runs a test case, handling a potential exception. -}
runTestCase :: TestCase -> IO TestCaseResult
runTestCase tc = do
  E.catch (do
             putStr $ if testPassed tc then "" else ""
             return $ testResult tc)
          (\ (E.SomeException e) -> do
             return $
              TestCaseResult (testIndex tc)
                  ("[" ++ show (testIndex tc) ++ "][-/] " ++ testDescr tc 
                    ++ ": EXCEPTION: " ++ show e)
                  0
                  (show e == "Prelude.undefined") True)

{- use this for a laboratory situation; prints only the first 2 of the undefined exercises -}
quickCheck :: [TestPP.TestData] -> IO ()
quickCheck = runTests False 2

{- use this for the vmchecker; prepends each test case with the points accumulated -}
vmCheck :: [TestPP.TestData] -> IO ()
vmCheck = runTests True undefined

{- runs a set of testData. The first 2 arguments define if vmchecker mode should be active and how many undefined exercises to show. -}
runTests :: Bool -> Int -> [TestData] -> IO ()
runTests checkerMode showDefaults tests = do
  results <- mapM (mapM runTestCase . getTestCases) tests
  let 
    res = foldl showResult ([], []) results 
    in mapM putStr (reverse (fst res) ++
          ["Exercises not done: " ++ (show $ reverse $ snd res) ++ "\n"])
  printFinalGrade results
  where
    showResult (out, notdone) r = 
        if not checkerMode && isUndefined && length notdone >= showDefaults
                  then (out, notdoneNew)
                  else (concatMap printRes r : out, notdoneNew)
      where
        isUndefined = (and $ map testExcepted r) && (or $ map testSubjectUndefined r)
        notdoneNew = if isUndefined then testExercise (head r) : notdone else notdone
        printRes r = (if checkerMode then "+" ++ show (testScore r) ++ " " else "")
             ++ testMessage r ++ "\n"
    printFinalGrade rr = do
      putStr $ "Final grade: "
      putStrLn $ show $ sum $ concat $ map (map testScore) rr


