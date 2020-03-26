module TestPP 
  ( TestPP, runTestPP
  , assertVal, assertProp
  ) where

import qualified Control.Exception as E (catch, evaluate, SomeException (..))
import Test

-- Keep the grade in testData
type TestPP a = Test Float a

getTestData :: TestPP a -> TestData Float
getTestData t = execTest t emptyTD

printTestCase :: TestCase Float -> IO ()
printTestCase tc = do
  putStr $ testName tc
  putStr $ " [" ++ show (testData tc) ++ "]: "
  E.catch (putStrLn $ getPassed (testPassed tc))
          (\ (E.SomeException e) -> putStrLn $ show e)
  where
  getPassed p = if p then "PASSED"
                     else "FAILED"

printFinalGrade :: TestData Float -> IO ()
printFinalGrade td = do
  putStr $ "Final grade: "
  showFinalGrade td
  where
  showFinalGrade td = mapM getGrade td >>= putStrLn . show . sum
  getGrade tc = E.catch (E.evaluate $ if testPassed tc then testData tc else 0)
                      (\ (E.SomeException _) -> return 0)

runTestPP :: TestPP a -> IO ()
runTestPP t = do
  let td = getTestData t
  mapM_ printTestCase td
  printFinalGrade td
