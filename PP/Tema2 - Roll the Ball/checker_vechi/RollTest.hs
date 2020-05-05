{-# LANGUAGE MultiParamTypeClasses #-}

module RollTest where

import RollLevels

import TestPP
import Pipes
import RollTheBall
import RollLevels
import Search
import AStarHeuristic
import Data.Set as S
import Data.List as L
import Data.Maybe
import Data.Hashable
import ProblemState
import Control.Monad (join)
import Control.Arrow ((***))
import Control.Monad.Trans.State.Lazy (runState, modify)
import Data.Graph.AStar
import qualified Data.HashSet as H

testAddObject :: TestPP ()
testAddObject = tests 1 7
    [ testString "add emptyCells" 1
        [endl, emptySpace, emptyCell, endl, emptyCell, emptySpace, endl]
        $ show $ addCell (emptyCell, (0,1)) $ addCell (emptyCell, (1,0)) $ emptyLvl
    , testString "add winCells" 1
        [endl, winLeft, winRight, endl, winUp, winDown, endl]
        $ show $ addCell (winLeft, (0,0)) $ addCell (winRight, (0,1))
               $ addCell (winUp, (1,0)) $ addCell (winDown, (1,1)) $ emptyLvl
    , testString "add startCells" 1
        [endl, startLeft, startRight, endl, startUp, startDown, endl]
        $ show $ addCell (startLeft, (0,0)) $ addCell (startRight, (0,1))
               $ addCell (startUp, (1,0)) $ addCell (startDown, (1,1)) $ emptyLvl
    , testString "add corners" 1
        [endl, topLeft, topRight, endl, botLeft, botRight, endl]
        $ show $ addCell (topLeft, (0,0)) $ addCell (topRight, (0,1))
               $ addCell (botLeft, (1,0)) $ addCell (botRight, (1,1)) $ emptyLvl       
    , testString "add pp" 2
        stringPePe $ show levelPePe
    , testString "out of bounds" 1
        stringPePe $ show $ addCell (startLeft, (-1,0)) $ addCell (startRight, (8,7)) $ levelPePe
    ]

testCreateLevel :: TestPP ()
testCreateLevel = tests 2 8
  [ testString "emptyLevel (1, 1)" 1 
      empty1String $ show $ emptyLvl
    , testString "level1 (3,3)" 1
      level1String $ show $ level1
    , testString "level2 (3,3)" 1
      level2String $ show level2
    , testString "level3 (3,3)" 1
      level3String $ show level3
    , testString "level4 (4,4)" 1
      level4String $ show level4
    , testString "level5 (4,4)" 1
      level5String $ show level5
      ]

testMove :: TestPP ()
testMove = tests 3 10
      [ testString "move horPipe (3,3) Left" 1
        move1String $ show $ moveCell (3,2) West $ level1,
        testString "move botLeft (3,1) Right" 1
        move2String $ show $ moveCell (3,0) East $ level1,
        testString "move emptyCell Down" 1
        move3String $ show $ moveCell (2,1) South $ level2,
        testString "move Start" 1
        level2String $ show $ moveCell (0,0) South $ level2,
        testString "move End" 1
        level2String $ show $ moveCell (3,3) North $ level2,
        testString "move without space" 1
        level2String $ show $ moveCell (0,3) South $ level2,
        testString "move outside bounds" 2
        level2String $ show $ moveCell (2,3) East $ level2
      ]
    
testWin :: TestPP ()
testWin = tests 4 10 [ 
        testCond "won on level1" 1
          (wonLevel (moveCell (2,1) South level1)
            && (not . wonLevel $ level1)),
        testCond "won on level2" 1
          (wonLevel level2Solved
            && (not . wonLevel $ level2)),
        testCond "won on level3" 1
          (wonLevel level3Solved
            && (not . wonLevel $ level3)),
        testCond "won on level4" 1
          (wonLevel level4Solved
            && (not . wonLevel $ level4)),
        testCond "won on level5" 1
          (wonLevel level5Solved
            && (not . wonLevel $ level5))
        ]

testSuccessors :: TestPP()
testSuccessors = tests 5 10 [
        testCond "check successors 1" 1
            (checkSuccessors level1 succLevel1),
        testCond "check successors 2" 1
            (checkSuccessors level2 succLevel2),
        testCond "check successors 3" 1
            (checkSuccessors level3 succLevel3),
        testCond "check successors 4" 1
            (checkSuccessors level4 succLevel4),
        testCond "check successors 5" 1
            (checkSuccessors level5 succLevel5)
   ]


testBFS :: TestPP()
testBFS = tests 6 15 [
        testCond "check bfs 1" 1
            (checkBFS (bfs $ createStateSpace level1) 2),
        testCond "check bfs 2" 1
            (checkBFS (bfs $ createStateSpace level2) 3),
        testCond "check bfs 3" 1
            (checkBFS (bfs $ createStateSpace level3) 2),
        testCond "check bfs 4" 1
            (checkBFS (bfs $ createStateSpace level4) 2),
        testCond "check bfs 5" 1
            (checkBFS (bfs $ createStateSpace level5) 2)
   ]

testbidirBFS :: TestPP()
testbidirBFS = tests 7 20 [
        testCond "check bidirBFS 1" 1
            (checkbidirBFS (bidirBFS (createStateSpace level2) (createStateSpace level2Solved))),
        testCond "check bidirBFS 2" 1
            (checkbidirBFS (bidirBFS (createStateSpace level3) (createStateSpace level3Solved))),
        testCond "check bidirBFS 3" 1
            (checkbidirBFS (bidirBFS (createStateSpace level4) (createStateSpace level4Solved))),
        testCond "check bidirBFS 4" 1
            (checkbidirBFS (bidirBFS (createStateSpace level5) (createStateSpace level5Solved)))
   ]


testExtractPath :: TestPP ()
testExtractPath = tests 8 10 [
        testCond "check extractPath 1" 1
            (checkExtract (nodeChildren (createStateSpace level1) !! 0) (createStateSpace level1)),
        testCond "check extractPath 2" 1
            (checkExtract (nodeChildren (createStateSpace level2) !! 1) (createStateSpace level2)),
        testCond "check extractPath 3" 1
            (checkExtract (nodeChildren (createStateSpace level3) !! 0) (createStateSpace level3)),
        testCond "check extractPath 4" 1
            (checkExtract (nodeChildren (createStateSpace level4) !! 2) (createStateSpace level4)),
        testCond "check extractPath 5" 1
            (checkExtract (nodeChildren (createStateSpace level5) !! 0) (createStateSpace level5))
    ]

testSolve :: TestPP()
testSolve = tests 9 10 [
        testCond "check solve 1" 1
            (checkSolve (solve level1 level1Solved)),
        testCond "check solve 2" 1
            (checkSolve (solve level2 level2Solved)),
        testCond "check solve 3" 1
            (checkSolve (solve level3 level3Solved)),
        testCond "check solve 4" 1
            (checkSolve (solve level4 level4Solved)),
        testCond "check solve 5" 1
            (checkSolve (solve level5 level5Solved))
   ]


testBonus :: TestPP()
testBonus = tests 10 20 [
	testCond "hashWithSalt on different levels returns different values" 4
		(hashWithSalt 0 level1 /= hashWithSalt 0 level2),
	testCond "nonTrivialHeuristic works on level2" 4
		(checkImprovement level2),	
	testCond "nonTrivialHeuristic works on level3" 4
		(checkImprovement level3),	
	testCond "nonTrivialHeuristic works on level4" 4
		(checkImprovement level4)	
	]
		where
			checkImprovement level = (<) (countExpandedNonTrivial level)
							(countExpandedTrivial level) 
			countExpandedTrivial start = 
				snd $ counterAStar trivialHeuristic start
			countExpandedNonTrivial start = 
				snd $ counterAStar nonTrivialHeuristic start


main :: IO()
main = runTestPP $ sequence_ [ testAddObject
                             , testCreateLevel
                             , testMove
                             , testWin
                             , testSuccessors
                             , testBFS
                             , testbidirBFS
                             , testExtractPath
                             , testSolve
                             , testBonus
                             ]

move1String :: [Char]
move1String = [ endl,
    startDown, emptyCell, emptyCell, emptyCell, endl,
    verPipe, emptyCell, emptyCell, emptyCell, endl,
    verPipe, horPipe, emptyCell, emptyCell, endl,
    botLeft, horPipe, emptySpace, winLeft, endl
    ]

move2String :: [Char]
move2String = [ endl,
    startDown, emptyCell, emptyCell, emptyCell, endl,
    verPipe, emptyCell, emptyCell, emptyCell, endl,
    verPipe, horPipe, emptyCell, emptyCell, endl,
    emptySpace, botLeft, horPipe, winLeft, endl
    ]

move3String :: [Char]
move3String = [ endl,
    startDown, emptyCell, emptyCell, emptyCell, endl,
    emptySpace, verPipe, emptySpace, emptyCell, endl,
    verPipe, emptySpace, horPipe, emptySpace, endl,
    botLeft, emptyCell, horPipe, winLeft, endl
    ]

checkSet :: (Eq a, Ord a) => ([a], [a]) -> Bool
checkSet = eq . (join (***) S.fromList)
eq :: Eq a => (a,a) -> Bool
eq (x,y) = x == y

succLevel1 :: [(Position, Directions)]
succLevel1 = [((3,2),West),((3,0),East),((2,1),South)]
succLevel2 :: [(Position, Directions)]
succLevel2 = [((3,2),West),((3,0),East),((2,2),North),
              ((2,2),East),((2,1),South),((2,0),North),
              ((1,3),South),((1,3),West),((1,1),West),
              ((1,1),East),((0,2),South)]
succLevel3 :: [(Position, Directions)]
succLevel3 = [((3,3),West),((2,2),South),((2,1),South),((2,0),South)]
succLevel4 :: [(Position, Directions)]
succLevel4 = [((4,2),North),((4,0),North),((3,3),West),((3,3),East),
              ((3,1),West),((3,1),East),((2,4),North),((2,4),South),
              ((2,2),South),((2,1),West),((1,3),East),((1,2),North),
              ((1,1),West),((0,4),South),((0,3),West)]
succLevel5 :: [(Position, Directions)]
succLevel5 = [((4,4),North),((4,1),North),((3,3),North),((3,3),East),
              ((3,2),West),((2,4),South),((2,4),West),((2,2),West),
              ((2,2),East),((2,0),North),((2,0),East),((1,3),South),
              ((1,1),South),((1,1),West),((0,0),South)]


checkSuccessors :: Level -> [(Position, Directions)] -> Bool
checkSuccessors lvl lst = checkSet (succ1, succ2) where
        succ1 = successors lvl
        succ2 = L.map (\(pos,dir) -> ((pos,dir), moveCell pos dir lvl)) lst


checkBFS :: Eq s => [([Node s a], [Node s a])] -> Int -> Bool
checkBFS bfsStream tk = (not (L.null bfsList)) && (nodeChildrenInFrontier bfsList) && (validOrderInFrontier bfsList)
    where sorted xs = and $ zipWith (<=) xs (tail xs) 
          nodeChildrenInFrontier xs = and $ zipWith (\(_, fr1) (nds, _) -> (L.map nodeState nds) `subsetOf` (L.map nodeState (nodeChildren (head fr1)))) xs (tail xs)
          bfsList = take tk bfsStream
          validOrderInFrontier xs = (and $ L.map (\(x, y) -> ((L.map nodeState x) `subsetOf` (L.map nodeState y)) && (sorted $ L.map nodeDepth y)) xs)

checkbidirBFS :: Eq s => (Node s a, Node s a) -> Bool
checkbidirBFS (nd1, nd2) = ((nodeState nd1) == (nodeState nd2)) && ((nodeState $ fromJust $ nodeParent nd1) /= (nodeState $ fromJust $ nodeParent nd2))

checkExtract :: (Eq a, Eq s) => (Node s a) -> (Node s a) -> Bool
checkExtract nd start = fstState == (nodeState start) && (fstAction == Nothing) && (sndAction == (nodeAction nd))
    where path = extractPath nd
          fstState = snd $ head path
          fstAction = fst $ head path
          sndAction = fst $ head $ tail path


checkSolve :: [(Maybe (Position, Directions), Level)] -> Bool
checkSolve steps = (L.map (\x -> snd x) (tail steps)) == resultingMoves && (isGoal $ last resultingMoves)
    where moves = zipWith (\x1 x2 -> (fst x2, snd x1)) steps (tail steps)
          resultingMoves = L.map (\(Just (pos, dir), st) -> moveCell pos dir st) moves



counterAStar :: (Ord a, Num a)
        => (Level -> a)
        -> Level
        -> (Maybe [Level], Int)
counterAStar heuristic start =
    flip runState 0 $ aStarM (return . neighbours)
                             (((.).(.)) return distance)
                             (return . heuristic)
                             (\level -> modify (+ 1) >> return (isGoal level))
                             (return start)

xs `subsetOf` ys = L.null $ L.filter (not . (`elem` ys)) xs
