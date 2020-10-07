{-# OPTIONS_GHC -Wall #-}
{-# LANGUAGE EmptyDataDecls, MultiParamTypeClasses,
             TypeSynonymInstances, FlexibleInstances,
             InstanceSigs #-}
module RollLevels where
import RollTheBall
import Pipes

empty1String :: [Char]
empty1String = [endl,
            emptySpace, emptySpace, endl,
            emptySpace, emptySpace, endl]

emptyLvl :: Level
emptyLvl = emptyLevel (1,1)


level1List :: [(Char, Position)]
level1List = [
    (startDown, (0,0)), (emptyCell, (0,1)), (emptyCell, (0,2)), (emptyCell, (0,3)),
    (verPipe, (1,0)), (emptyCell, (1,1)), (emptyCell, (1,2)), (emptyCell, (1,3)),
    (verPipe, (2,0)), (horPipe, (2,1)), (emptyCell, (2,2)), (emptyCell, (2,3)),
    (botLeft, (3,0)), (horPipe, (3,2)), (winLeft, (3,3))
    ]

level1String :: [Char]
level1String = [ endl,
    startDown, emptyCell, emptyCell, emptyCell, endl,
    verPipe, emptyCell, emptyCell, emptyCell, endl,
    verPipe, horPipe, emptyCell, emptyCell, endl,
    botLeft, emptySpace, horPipe, winLeft, endl
    ]

level1 :: Level
level1 = createLevel (3,3) level1List

level1Solved :: Level
level1Solved = createLevel (3,3) [
    (startDown, (0,0)), (emptyCell, (0,1)), (emptyCell, (0,2)), (emptyCell, (0,3)),
    (verPipe, (1,0)), (emptyCell, (1,1)), (emptyCell, (1,2)), (emptyCell, (1,3)),
    (verPipe, (2,0)), (emptyCell, (2,2)), (emptyCell, (2,3)),
    (botLeft, (3,0)), (horPipe, (3,1)), (horPipe, (3,2)), (winLeft, (3,3))
    ]

level2List :: [(Char, Position)]
level2List = [
    (startDown, (0,0)), (emptyCell, (0,1)), (emptyCell, (0,2)), (emptyCell, (0,3)),
    (verPipe, (1,1)), (emptyCell, (1,3)),
    (verPipe, (2,0)), (emptyCell, (2,1)), (horPipe, (2,2)),
    (botLeft, (3,0)), (horPipe, (3,2)), (winLeft, (3,3))
    ]


level2String :: [Char]
level2String = [endl,
    startDown, emptyCell, emptyCell, emptyCell, endl,
    emptySpace, verPipe, emptySpace, emptyCell, endl,
    verPipe, emptyCell, horPipe, emptySpace, endl,
    botLeft, emptySpace, horPipe, winLeft, endl
         ]

level2 :: Level
level2 = createLevel (3,3) level2List

level2Solved :: Level
level2Solved = createLevel (3,3) [
    (startDown, (0,0)), (emptyCell, (0,1)), (emptyCell, (0,2)), (emptyCell, (0,3)),
    (verPipe, (1,0)), (emptyCell, (1,3)),
    (verPipe, (2,0)), (emptyCell, (2,1)),
    (botLeft, (3,0)), (horPipe, (3, 1)), (horPipe, (3,2)), (winLeft, (3,3))
    ]

level3List :: [(Char, Position)]
level3List = [
    (startDown, (0,0)), (emptyCell, (0,1)), (emptyCell, (0,2)), (emptyCell, (0,3)),
    (verPipe, (1,0)), (emptyCell, (1,1)), (emptyCell, (1,2)), (winDown, (1,3)),
    (botLeft, (2,0)), (horPipe, (2,1)), (botRight, (2,2)), (emptyCell, (2,3)),
    (horPipe, (3,3))
    ]

level3String :: [Char]
level3String = [ endl,
    startDown, emptyCell, emptyCell, emptyCell, endl,
    verPipe, emptyCell, emptyCell, winDown, endl,
    botLeft, horPipe, botRight, emptyCell, endl,
    emptySpace, emptySpace, emptySpace, horPipe, endl
    ]

level3 :: Level
level3 = createLevel (3,3) level3List

level3Solved :: Level
level3Solved = createLevel (3,3) [
  (startDown, (0,0)), (emptyCell, (0,1)), (emptyCell, (0,2)), (emptyCell, (0,3)),
  (verPipe, (1,0)), (emptyCell, (1,1)), (emptyCell, (1,2)), (winDown, (1,3)),
  (botLeft, (2,0)), (horPipe, (2,1)), (horPipe, (2,2)), (botRight, (2,3)),
  (emptyCell, (3,3))
  ]

level3Solved2 :: Level
level3Solved2 = createLevel (3,3) [
  (startDown, (0,0)), (emptyCell, (0,1)), (emptyCell, (0,2)), (emptyCell, (0,3)),
  (verPipe, (1,0)), (emptyCell, (1,1)), (emptyCell, (1,2)), (winDown, (1,3)),
  (botLeft, (2,0)), (horPipe, (2,1)), (horPipe, (2,2)), (botRight, (2,3)),
  (emptyCell, (3,3)), (emptySpace, (3, 2))
  ]

-- Deimos level 2
level4List :: [(Char, Position)]
level4List = [
    (startRight, (0,1)), (horPipe, (0,3)), (topRight, (0,4)),
    (topLeft, (1,1)), (horPipe, (1,2)), (botRight, (1,3)),
    (verPipe, (2,1)), (horPipe, (2,2)), (horPipe, (2,3)), (horPipe, (2,4)),
    (botLeft, (3,1)), (topRight, (3,3)),
    (emptyCell, (4,0)), (emptyCell, (4,1)), (emptyCell, (4,2)), (winUp, (4,3))
    ]

level4String :: [Char]
level4String = [ endl,
    emptySpace, startRight, emptySpace, horPipe, topRight, endl,
    emptySpace, topLeft, horPipe, botRight, emptySpace, endl,
    emptySpace, verPipe, horPipe, horPipe, horPipe, endl,
    emptySpace, botLeft, emptySpace, topRight, emptySpace, endl,
    emptyCell, emptyCell, emptyCell, winUp, emptySpace, endl
    ]

level4 :: Level
level4 = createLevel (4,4) level4List

level4Solved :: Level
level4Solved = createLevel (4,4) [
  (startRight, (0,1)), (horPipe, (0,2)), (horPipe ,(0,3)), (topRight ,(0,4)),
  (topLeft ,(1,2)), (horPipe ,(1,3)), (botRight, (1,4)),
  (verPipe ,(2,2)), (horPipe ,(2,3)), (horPipe, (2, 4)),
  (botLeft ,(3,2)), (topRight ,(3,3)),
  (emptyCell, (4,0)), (emptyCell, (4,1)), (emptyCell ,(4,2)), (winUp ,(4,3))
  ]

-- Deimos level 1
level5List :: [(Char, Position)]
level5List = [
    (emptyCell, (0,0)), (emptyCell, (0,1)), (emptyCell, (0,2)), (horPipe, (0,3)), (botRight, (0,4)),
    (botRight, (1,1)), (horPipe, (1,2)), (horPipe, (1,3)), (topRight, (1,4)),
    (topLeft, (2,0)), (topLeft, (2,2)), (botRight, (2,4)),
    (winDown, (3,0)), (verPipe, (3,2)), (topLeft, (3,3)),
    (botLeft, (4,0)), (verPipe, (4,1)), (botRight, (4,2)), (startUp, (4,3)), (verPipe, (4,4))
    ]

level5String :: [Char]
level5String = [ endl,
    emptyCell, emptyCell, emptyCell, horPipe, botRight, endl,
    emptySpace, botRight, horPipe, horPipe, topRight, endl,
    topLeft, emptySpace, topLeft, emptySpace, botRight, endl,
    winDown, emptySpace, verPipe, topLeft, emptySpace, endl,
    botLeft, verPipe, botRight, startUp, verPipe, endl
    ]

level5 :: Level
level5 = createLevel (4,4) level5List

level5Solved :: Level
level5Solved = createLevel (4,4) [
    (emptyCell, (0,0)), (emptyCell, (0,1)), (emptyCell, (0,2)), (horPipe, (0,3)), (botRight, (0,4)),
    (botRight, (1,0)),
    (topLeft, (2,0)), (topLeft, (2,1)), (horPipe, (2,2)), (horPipe, (2,3)), (topRight, (2,4)),
    (winDown, (3,0)), (verPipe, (3,1)), (verPipe, (3,2)), (topLeft, (3,3)), (botRight, (3,4)),
    (botLeft, (4,0)), (botRight, (4,1)), (startUp, (4,3)), (verPipe, (4,4))
    ]

won1String :: [Char]
won1String = [ endl,
    startDown, emptyCell, emptyCell, emptyCell, endl,
    verPipe, emptyCell, emptyCell, emptyCell, endl,
    verPipe, emptySpace, emptyCell, emptyCell, endl,
    botLeft, horPipe, horPipe, winLeft, endl
    ]

levelPePe :: Level
levelPePe = addCell (topLeft, (0,0)) $ addCell (horPipe, (0,1)) $ addCell (topRight, (0,2))
            $ addCell (topLeft, (0,4)) $ addCell (horPipe, (0,5)) $ addCell (topRight, (0,6))
            $ addCell (verPipe, (1,0)) $ addCell (verPipe, (1,2)) $ addCell (verPipe, (1,4))
            $ addCell (verPipe, (1,6)) $ addCell (verPipe, (2,0)) $ addCell (horPipe, (2,1))
            $ addCell (botRight, (2,2)) $ addCell (verPipe, (2,4)) $ addCell (horPipe, (2,5))
            $ addCell (botRight, (2,6)) $ addCell (verPipe, (3,0)) $ addCell (verPipe, (3, 4))
            $ emptyLevel (3,6)

stringPePe :: [Char]
stringPePe = [ endl, 
    topLeft, horPipe, topRight, emptySpace, topLeft, horPipe, topRight, endl,
    verPipe, emptySpace, verPipe, emptySpace, verPipe, emptySpace, verPipe, endl,
    verPipe, horPipe, botRight, emptySpace, verPipe, horPipe, botRight, endl,
    verPipe, emptySpace, emptySpace, emptySpace, verPipe, emptySpace, emptySpace, endl
    ]
