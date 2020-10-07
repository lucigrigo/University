module TestPP 
  ( TestPP, runTestPP, liftIO
  , assertVal, testCond, testVal, testString, testOne, tests, test
  ) where

import qualified Control.Exception as E (catch, evaluate, SomeException (..))
import Control.Monad.IO.Class (liftIO)
import Test
import CheckerCore

-- Keep the grade in testData
type TestPP a = Test Float a

getTestData :: TestPP a -> IO (TestData Float)
getTestData t = execTest t emptyTD

printTestCase :: TestCase Float -> IO (TestCase Float)
printTestCase tc = do
  E.catch (do
             tp <- testPassed tc
             putStr $ if tp then "[OK]" else "[--]"
             putStr $ testName tc ++ ": "
             putStrLn $ putResult tp (testData tc) (testError tc)
             return $ if tp then tc else tc { testResult = 0 })
          (\ (E.SomeException e) -> do
             putStr $ "[-/]" ++ testName tc ++ ": EXCEPTION: "
             print e
             return tc { testResult = 0 })
  where
  putResult p d e = if p then "+" ++ (show d) ++ " PASSED"
                      else "FAILED: " ++ e

printFinalGrade :: TestData Float -> IO ()
printFinalGrade td = do
  putStr $ "Final grade: "
  print $ round $ sum $ map testResult td

printFinalPepe :: TestData Float -> IO ()
printFinalPepe td = do
  writeFile "Important.txt" message
  where
    grade = round (sum $ map testResult td)
    message
      | grade <= 25 = angry
      | grade <= 50 = okay
      | grade <= 75  = interested
      | grade <= 100 = happy
      | grade > 100 = extatic

runTestPP :: TestPP a -> IO ()
runTestPP t = do
  td <- getTestData t
  td' <- mapM printTestCase td
  printFinalGrade td'
  printFinalPepe td'
