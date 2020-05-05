{-# LANGUAGE FlexibleInstances, UndecidableInstances #-}

module Interactive where
import RollTheBall
import Test
import RollLevels

import qualified System.Process as SP


workingOs :: Os
workingOs = Windows

data Os = Windows | Linux
    deriving (Show, Eq)

cls = do
    case workingOs of
        Linux -> SP.system "clear"
        Windows -> SP.system "cls"

newLvl :: Position -> [Char] -> Level -> Level    
newLvl pos z lvl = case z of
    "w" -> moveCell pos North lvl
    "s" -> moveCell pos South lvl
    "a" -> moveCell pos West lvl
    "d" -> moveCell pos East lvl
    _ -> lvl

play :: Level -> IO()
play lvl
    | wonLevel lvl = do 
        putStr $ show lvl
        putStr "Level completed! Well done!\n"
    | otherwise = do
        putStr $ show lvl
        putStr "Type row: "
        x <- readLn :: IO Int
        putStr "Type column: "
        y <- readLn :: IO Int
        putStr "Type Direction w/a/s/d: "
        z <- getLine
        play $ newLvl (x,y) z lvl

