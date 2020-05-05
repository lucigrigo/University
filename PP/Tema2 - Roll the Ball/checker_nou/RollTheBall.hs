{-# OPTIONS_GHC -Wall #-}
{-# LANGUAGE EmptyDataDecls, MultiParamTypeClasses,
             TypeSynonymInstances, FlexibleInstances,
             InstanceSigs #-}
module RollTheBall where
import Pipes
import ProblemState
import Data.Array as A
-- import Debug.Trace as T

-- succLevel1 :: [(Position, Directions)]
-- succLevel1 = [((3,2),West),((3,0),East),((2,1),South)]
-- succLevel2 :: [(Position, Directions)]
-- succLevel2 = [((3,2),West),((3,0),East),((2,2),North),
--               ((2,2),East),((2,1),South),((2,0),North),
--               ((1,3),South),((1,3),West),((1,1),West),
--               ((1,1),East),((0,2),South)]
-- succLevel3 :: [(Position, Directions)]
-- succLevel3 = [((3,3),West),((2,2),South),((2,1),South),((2,0),South)]
-- succLevel4 :: [(Position, Directions)]
-- succLevel4 = [((4,2),North),((4,0),North),((3,3),West),((3,3),East),
--               ((3,1),West),((3,1),East),((2,4),North),((2,4),South),
--               ((2,2),South),((2,1),West),((1,3),East),((1,2),North),
--               ((1,1),West),((0,4),South),((0,3),West)]
-- succLevel5 :: [(Position, Directions)]
-- succLevel5 = [((4,4),North),((4,1),North),((3,3),North),((3,3),East),
--               ((3,2),West),((2,4),South),((2,4),West),((2,2),West),
--               ((2,2),East),((2,0),North),((2,0),East),((1,3),South),
--               ((1,1),South),((1,1),West),((0,0),South)]


-- empty1String :: [Char]
-- empty1String = [endl,
--             emptySpace, emptySpace, endl,
--             emptySpace, emptySpace, endl]

-- emptyLvl :: Level
-- emptyLvl = emptyLevel (1,1)


-- level1List :: [(Char, Position)]
-- level1List = [
--     (startDown, (0,0)), (emptyCell, (0,1)), (emptyCell, (0,2)), (emptyCell, (0,3)),
--     (verPipe, (1,0)), (emptyCell, (1,1)), (emptyCell, (1,2)), (emptyCell, (1,3)),
--     (verPipe, (2,0)), (horPipe, (2,1)), (emptyCell, (2,2)), (emptyCell, (2,3)),
--     (botLeft, (3,0)), (horPipe, (3,2)), (winLeft, (3,3))
--     ]

-- level1String :: [Char]
-- level1String = [ endl,
--     startDown, emptyCell, emptyCell, emptyCell, endl,
--     verPipe, emptyCell, emptyCell, emptyCell, endl,
--     verPipe, horPipe, emptyCell, emptyCell, endl,
--     botLeft, emptySpace, horPipe, winLeft, endl
--     ]

-- level1 :: Level
-- level1 = createLevel (3,3) level1List

-- level1Solved :: Level
-- level1Solved = createLevel (3,3) [
--     (startDown, (0,0)), (emptyCell, (0,1)), (emptyCell, (0,2)), (emptyCell, (0,3)),
--     (verPipe, (1,0)), (emptyCell, (1,1)), (emptyCell, (1,2)), (emptyCell, (1,3)),
--     (verPipe, (2,0)), (emptyCell, (2,2)), (emptyCell, (2,3)),
--     (botLeft, (3,0)), (horPipe, (3,1)), (horPipe, (3,2)), (winLeft, (3,3))
--     ]

-- level2List :: [(Char, Position)]
-- level2List = [
--     (startDown, (0,0)), (emptyCell, (0,1)), (emptyCell, (0,2)), (emptyCell, (0,3)),
--     (verPipe, (1,1)), (emptyCell, (1,3)),
--     (verPipe, (2,0)), (emptyCell, (2,1)), (horPipe, (2,2)),
--     (botLeft, (3,0)), (horPipe, (3,2)), (winLeft, (3,3))
--     ]


-- level2String :: [Char]
-- level2String = [endl,
--     startDown, emptyCell, emptyCell, emptyCell, endl,
--     emptySpace, verPipe, emptySpace, emptyCell, endl,
--     verPipe, emptyCell, horPipe, emptySpace, endl,
--     botLeft, emptySpace, horPipe, winLeft, endl
--          ]

-- level2 :: Level
-- level2 = createLevel (3,3) level2List

-- level2Solved :: Level
-- level2Solved = createLevel (3,3) [
--     (startDown, (0,0)), (emptyCell, (0,1)), (emptyCell, (0,2)), (emptyCell, (0,3)),
--     (verPipe, (1,0)), (emptyCell, (1,3)),
--     (verPipe, (2,0)), (emptyCell, (2,1)),
--     (botLeft, (3,0)), (horPipe, (3, 1)), (horPipe, (3,2)), (winLeft, (3,3))
--     ]

-- level3List :: [(Char, Position)]
-- level3List = [
--     (startDown, (0,0)), (emptyCell, (0,1)), (emptyCell, (0,2)), (emptyCell, (0,3)),
--     (verPipe, (1,0)), (emptyCell, (1,1)), (emptyCell, (1,2)), (winDown, (1,3)),
--     (botLeft, (2,0)), (horPipe, (2,1)), (botRight, (2,2)), (emptyCell, (2,3)),
--     (horPipe, (3,3))
--     ]

-- level3String :: [Char]
-- level3String = [ endl,
--     startDown, emptyCell, emptyCell, emptyCell, endl,
--     verPipe, emptyCell, emptyCell, winDown, endl,
--     botLeft, horPipe, botRight, emptyCell, endl,
--     emptySpace, emptySpace, emptySpace, horPipe, endl
--     ]

-- level3 :: Level
-- level3 = createLevel (3,3) level3List

-- level3Solved :: Level
-- level3Solved = createLevel (3,3) [
--   (startDown, (0,0)), (emptyCell, (0,1)), (emptyCell, (0,2)), (emptyCell, (0,3)),
--   (verPipe, (1,0)), (emptyCell, (1,1)), (emptyCell, (1,2)), (winDown, (1,3)),
--   (botLeft, (2,0)), (horPipe, (2,1)), (horPipe, (2,2)), (botRight, (2,3)),
--   (emptyCell, (3,3))
--   ]

-- level3Solved2 :: Level
-- level3Solved2 = createLevel (3,3) [
--   (startDown, (0,0)), (emptyCell, (0,1)), (emptyCell, (0,2)), (emptyCell, (0,3)),
--   (verPipe, (1,0)), (emptyCell, (1,1)), (emptyCell, (1,2)), (winDown, (1,3)),
--   (botLeft, (2,0)), (horPipe, (2,1)), (horPipe, (2,2)), (botRight, (2,3)),
--   (emptyCell, (3,3)), (emptySpace, (3, 2))
--   ]

-- -- Deimos level 2
-- level4List :: [(Char, Position)]
-- level4List = [
--     (startRight, (0,1)), (horPipe, (0,3)), (topRight, (0,4)),
--     (topLeft, (1,1)), (horPipe, (1,2)), (botRight, (1,3)),
--     (verPipe, (2,1)), (horPipe, (2,2)), (horPipe, (2,3)), (horPipe, (2,4)),
--     (botLeft, (3,1)), (topRight, (3,3)),
--     (emptyCell, (4,0)), (emptyCell, (4,1)), (emptyCell, (4,2)), (winUp, (4,3))
--     ]

-- level4String :: [Char]
-- level4String = [ endl,
--     emptySpace, startRight, emptySpace, horPipe, topRight, endl,
--     emptySpace, topLeft, horPipe, botRight, emptySpace, endl,
--     emptySpace, verPipe, horPipe, horPipe, horPipe, endl,
--     emptySpace, botLeft, emptySpace, topRight, emptySpace, endl,
--     emptyCell, emptyCell, emptyCell, winUp, emptySpace, endl
--     ]

-- level4 :: Level
-- level4 = createLevel (4,4) level4List

-- level4Solved :: Level
-- level4Solved = createLevel (4,4) [
--   (startRight, (0,1)), (horPipe, (0,2)), (horPipe ,(0,3)), (topRight ,(0,4)),
--   (topLeft ,(1,2)), (horPipe ,(1,3)), (botRight, (1,4)),
--   (verPipe ,(2,2)), (horPipe ,(2,3)), (horPipe, (2, 4)),
--   (botLeft ,(3,2)), (topRight ,(3,3)),
--   (emptyCell, (4,0)), (emptyCell, (4,1)), (emptyCell ,(4,2)), (winUp ,(4,3))
--   ]

-- -- Deimos level 1
-- level5List :: [(Char, Position)]
-- level5List = [
--     (emptyCell, (0,0)), (emptyCell, (0,1)), (emptyCell, (0,2)), (horPipe, (0,3)), (botRight, (0,4)),
--     (botRight, (1,1)), (horPipe, (1,2)), (horPipe, (1,3)), (topRight, (1,4)),
--     (topLeft, (2,0)), (topLeft, (2,2)), (botRight, (2,4)),
--     (winDown, (3,0)), (verPipe, (3,2)), (topLeft, (3,3)),
--     (botLeft, (4,0)), (verPipe, (4,1)), (botRight, (4,2)), (startUp, (4,3)), (verPipe, (4,4))
--     ]

-- level5String :: [Char]
-- level5String = [ endl,
--     emptyCell, emptyCell, emptyCell, horPipe, botRight, endl,
--     emptySpace, botRight, horPipe, horPipe, topRight, endl,
--     topLeft, emptySpace, topLeft, emptySpace, botRight, endl,
--     winDown, emptySpace, verPipe, topLeft, emptySpace, endl,
--     botLeft, verPipe, botRight, startUp, verPipe, endl
--     ]

-- level5 :: Level
-- level5 = createLevel (4,4) level5List

-- level5Solved :: Level
-- level5Solved = createLevel (4,4) [
--     (emptyCell, (0,0)), (emptyCell, (0,1)), (emptyCell, (0,2)), (horPipe, (0,3)), (botRight, (0,4)),
--     (botRight, (1,0)),
--     (topLeft, (2,0)), (topLeft, (2,1)), (horPipe, (2,2)), (horPipe, (2,3)), (topRight, (2,4)),
--     (winDown, (3,0)), (verPipe, (3,1)), (verPipe, (3,2)), (topLeft, (3,3)), (botRight, (3,4)),
--     (botLeft, (4,0)), (botRight, (4,1)), (startUp, (4,3)), (verPipe, (4,4))
--     ]

-- won1String :: [Char]
-- won1String = [ endl,
--     startDown, emptyCell, emptyCell, emptyCell, endl,
--     verPipe, emptyCell, emptyCell, emptyCell, endl,
--     verPipe, emptySpace, emptyCell, emptyCell, endl,
--     botLeft, horPipe, horPipe, winLeft, endl
--     ]

-- levelPePe :: Level
-- levelPePe = addCell (topLeft, (0,0)) $ addCell (horPipe, (0,1)) $ addCell (topRight, (0,2))
--             $ addCell (topLeft, (0,4)) $ addCell (horPipe, (0,5)) $ addCell (topRight, (0,6))
--             $ addCell (verPipe, (1,0)) $ addCell (verPipe, (1,2)) $ addCell (verPipe, (1,4))
--             $ addCell (verPipe, (1,6)) $ addCell (verPipe, (2,0)) $ addCell (horPipe, (2,1))
--             $ addCell (botRight, (2,2)) $ addCell (verPipe, (2,4)) $ addCell (horPipe, (2,5))
--             $ addCell (botRight, (2,6)) $ addCell (verPipe, (3,0)) $ addCell (verPipe, (3, 4))
--             $ emptyLevel (3,6)

-- stringPePe :: [Char]
-- stringPePe = [ endl, 
--     topLeft, horPipe, topRight, emptySpace, topLeft, horPipe, topRight, endl,
--     verPipe, emptySpace, verPipe, emptySpace, verPipe, emptySpace, verPipe, endl,
--     verPipe, horPipe, botRight, emptySpace, verPipe, horPipe, botRight, endl,
--     verPipe, emptySpace, emptySpace, emptySpace, verPipe, emptySpace, emptySpace, endl
--     ]
{-
    Direcțiile în care se poate mișca o piesa pe tablă
-}

data Directions = North | South | West | East
    deriving (Show, Eq, Ord)

{-
    Sinonim tip de date pentru reprezetarea unei perechi (Int, Int)
    care va reține coordonatele celulelor de pe tabla de joc
-}

type Position = (Int, Int)

{-
    Tip de date pentru reprezentarea celulelor tablei de joc
-}

-- data CellType = Empty | Basic | Passage | Star | Win | Start 

data Cell = Cell Position Char
    deriving (Eq, Ord)

{-
    Tip de date pentru reprezentarea nivelului curent
-}

data Level = Level Int (A.Array Position Cell) Int Int
    deriving (Eq, Ord)

{-
    *** Optional *** 
  
    Dacă aveți nevoie0cit clasele Eq și Ord pentru Level.
    În cazul acesta, eliminați deriving (Eq, Ord) din Level.
-}

{-
    *** TODO ***

    Instanțiati Level pe Show. 
    Atenție! Fiecare linie este urmată de \n (endl in Pipes).
-}

fShow:: Level -> String
fShow (Level _ cells _ dimY) = foldl f [] (A.elems cells) where
    f str (Cell (cx, cy) symbol)
        | (cx == 0) && (cy == 0) = str ++ [endl] ++ [symbol]
        | cy == dimY             = str ++ [symbol] ++ [endl]
        | otherwise              = str ++ [symbol]

instance Show Level 
    where show = fShow

{-
    *** TODO ***
    Primește coordonatele colțului din dreapta jos a hărții.
    Intoarce un obiect de tip Level în care tabla este populată
    cu EmptySpace. Implicit, colțul din stânga sus este (0,0)
-}

emptyLevel :: Position -> Level
emptyLevel (x, y) = Level 0 (array ((0, 0), (x, y)) [((a, b), 
    (Cell (a, b) emptySpace)) | a <- [0..x], b <- [0..y]]) x y

{-
    *** TODO ***

    Adaugă o celulă de tip Pipe în nivelul curent.
    Parametrul char descrie tipul de tile adăugat: 
        verPipe -> pipe vertical
        horPipe -> pipe orizontal
        topLeft, botLeft, topRight, botRight -> pipe de tip colt
        startUp, startDown, startLeft, startRight -> pipe de tip initial
        winUp, winDown, winLeft, winRight -> pipe de tip final
    Parametrul Position reprezintă poziția de pe hartă la care va fi adaugată
    celula, dacă aceasta este liberă (emptySpace).
-}

addCell :: (Char, Position) -> Level -> Level
addCell (s, (posX, posY)) (Level nr cells dimX dimY) 
    | (posX <) 0 || (posY < 0) || (posX > dimX) || (posY > dimY) = (Level nr cells dimX dimY)
    | (locationType /= emptySpace) = (Level nr cells dimX dimY)
    | otherwise = (Level (nr + 1) (cells A.// [((posX, posY), (Cell (posX, posY) s))]) dimX dimY) 
        where (Cell (_, _) locationType) = cells A.! (posX, posY)

{-
    *** TODO *** 

    Primește coordonatele colțului din dreapta jos al hărții și o listă de 
    perechi de tipul (caracter_celulă, poziția_celulei).
    Întoarce un obiect de tip Level cu toate celeule din listă agăugate pe
    hartă.
    Observatie: Lista primită ca parametru trebuie parcursă de la dreapta 
    la stanga.
-}
 
createLevel :: Position -> [(Char, Position)] -> Level
createLevel (x, y) inputParams = foldr addCell (emptyLevel (x, y)) inputParams

{-
    *** TODO ***

    Mișcarea unei celule în una din cele 4 direcții 
    Schimbul se poate face doar dacă celula vecină e goală (emptySpace).
    Celulele de tip start și win sunt imutabile.

    Hint: Dacă nu se poate face mutarea puteți lăsa nivelul neschimbat.
-}

moveCell :: Position -> Directions -> Level -> Level
moveCell (x, y) _ (Level nr cells dimX dimY) 
    | ((cellType == winUp) || (cellType == winDown) || (cellType == winLeft) 
    || (cellType == winRight) || (cellType == startUp) || (cellType == startDown) 
    || (cellType == startLeft) || (cellType == startRight)) || (cellType == emptySpace) = (Level nr cells dimX dimY)
        where (Cell (_, _) cellType) = cells A.! (x, y)

moveCell (x, y) West (Level nr cells dimX dimY)
    | y == 0 = (Level nr cells dimX dimY)
    | (nextType == emptySpace) = (Level (nr + 1) (cells A.// [((currX, currY), (Cell (currX, currY) emptySpace)) ,
     ((nextX, nextY), (Cell (nextX, nextY) currType))]) dimX dimY)
    | otherwise = (Level nr cells dimX dimY)
        where (Cell (currX, currY) currType) = cells A.! (x, y)
              (Cell (nextX, nextY) nextType) = cells A.! (x, y - 1)

moveCell (x, y) South (Level nr cells dimX dimY)
    | (x == dimX) = (Level nr cells dimX dimY) 
    | (nextType == emptySpace) = (Level (nr + 1) (cells A.// [((currX, currY), (Cell (currX, currY) emptySpace)) ,
     ((nextX, nextY), (Cell (nextX, nextY) currType))]) dimX dimY)
    | otherwise = (Level nr cells dimX dimY)
        where (Cell (currX, currY) currType) = cells A.! (x, y)
              (Cell (nextX, nextY) nextType) = cells A.! (x + 1, y)

moveCell (x, y) East (Level nr cells dimX dimY)
    | (y == dimY) = (Level nr cells dimX dimY)
    | (nextType == emptySpace) = (Level (nr + 1) (cells A.// [((currX, currY), (Cell (currX, currY) emptySpace)) , 
    ((nextX, nextY), (Cell (nextX, nextY) currType))]) dimX dimY)
    | otherwise = (Level nr cells dimX dimY)
        where (Cell (currX, currY) currType) = cells A.! (x, y)
              (Cell (nextX, nextY) nextType) = cells A.! (x, y + 1)

moveCell (x, y) North (Level nr cells dimX dimY) 
    | x == 0 = (Level nr cells dimX dimY)
    | (nextType == emptySpace) = (Level (nr + 1) (cells A.// [((currX, currY), (Cell (currX, currY) emptySpace)) , 
    ((nextX, nextY), (Cell (nextX, nextY) currType))]) dimX dimY)
    | otherwise = (Level nr cells dimX dimY)
        where (Cell (currX, currY) currType) = cells A.! (x, y)
              (Cell (nextX, nextY) nextType) = cells A.! (x - 1, y)

{-
    *** TODO ***

    Verifică dacă două celule se pot conecta.
    Atenție: Această funcție se aplică de la stânga la 
    dreapta(nu este comutativă).

    ex: connection botLeft horPipe = True (╚═)
        connection horPipe botLeft = False (═╚)
-}
connection :: Cell -> Cell -> Bool
connection (Cell (x1, y1) type1) (Cell (x2, y2) type2)
    | (x1 == x2) && ((y1 + 1) == y2) && (((type1 == winRight) || (type1 == startRight) || (type1 == botLeft) || (type1 == topLeft) || (type1 == horPipe)) 
    && ((type2 == winLeft) || (type2 == startLeft) || (type2 == botRight) || (type2 == topRight) || (type2 == horPipe))) = True 
    | (y1 == y2) && ((x1 + 1) == x2) && (((type1 == winDown) || (type1 == startDown) || (type1 == topLeft) || (type1 == topRight) || (type1 == verPipe)) 
    && ((type2 == winUp) || (type2 == startUp) || (type2 == botRight) || (type2 == botLeft) || (type2 == verPipe))) = True
    | otherwise = False

        -- | (x1 == x2) && ((y1 + 1) == y2) && ((((type1 == winRight) || (type1 == startRight) || (type1 == botLeft) || (type1 == topLeft) || (type1 == horPipe)) 
    -- && ((type2 == winLeft) || (type2 == startLeft) || (type2 == botRight) || (type2 == topRight) || (type2 == horPipe)))) = True 
    -- | (y1 == y2) && ((x1 + 1) == x2) && ((((type1 == winDown) || (type1 == startDown) || (type1 == topLeft) || (type1 == topRight) || (type1 == verPipe)) 
    -- && ((type2 == winUp) || (type2 == startUp) || (type2 == botRight) || (type2 == botLeft) || (type2 == verPipe)))) = True
    -- | otherwise = False
{-
    *** TODO ***

    Va returna True dacă jocul este câștigat, False dacă nu.
    Va verifica dacă celulele cu Pipe formează o cale continuă de la celula
    de tip inițial la cea de tip final.
    Este folosită în cadrul Interactive.
-}

-- f:: String
-- f = trace (level3Solved) (wonLevel level3Solved)

filterConnections:: (A.Array (Int, Int) Cell) -> [Cell]
filterConnections cells = filter (\(Cell (_, _) t) -> (t == startDown) || (t == startLeft) || (t == startRight) || (t == startUp)) (A.elems cells)

startChecking:: Int -> Int -> Directions -> (A.Array (Int, Int) Cell) -> Cell -> Bool
startChecking maxX maxY from cells (Cell (cx, cy) ct)
    | (ct == winDown) && (from == South) = True
    | (ct == winUp) && (from == North) = True
    | (ct == winLeft) && (from == West) = True
    | (ct == winRight) && (from == East) = True
    | (ct == startDown) && (cx /= maxX) = (connection cCell downCell) && (startChecking maxX maxY North cells downCell)
    | (ct == startLeft) && (cy /= 0) = (connection cCell leftCell) && (startChecking maxX maxY East cells leftCell)
    | (ct == startRight) && (cy /= maxY)= (connection cCell rightCell) && (startChecking maxX maxY West cells rightCell)
    | (ct == startUp) && (cx /= 0)= (connection cCell upCell) && (startChecking maxX maxY South cells upCell)
    | (ct == verPipe) && (from == North) && (cx /= maxX) = (connection cCell downCell) && (startChecking maxX maxY North cells downCell)
    | (ct == verPipe) && (from == South) && (cx /= 0) = (connection cCell upCell) && (startChecking maxX maxY South cells upCell)
    | (ct == horPipe) && (from == West) && (cy /= maxY) = (connection cCell rightCell) && (startChecking maxX maxY West cells rightCell)
    | (ct == horPipe) && (from == East) && (cy /= 0) = (connection cCell leftCell) && (startChecking maxX maxY East cells leftCell)
    | (ct == botLeft) && (from == North) && (cy /= maxY) = (connection cCell rightCell) && (startChecking maxX maxY West cells rightCell)
    | (ct == botLeft) && (from == East) && (cx /= 0) = (connection cCell upCell) && (startChecking maxX maxY South cells upCell)
    | (ct == topLeft) && (from == South) && (cy /= maxY) = (connection cCell rightCell) && (startChecking maxX maxY West cells rightCell)
    | (ct == topLeft) && (from == East) && (cx /= maxX) = (connection cCell downCell) && (startChecking maxX maxY North cells downCell)
    | (ct == botRight) && (from == West) && (cx /= 0) = (connection cCell upCell) && (startChecking maxX maxY South cells upCell)
    | (ct == botRight) && (from == North) && (cy /= 0) = (connection cCell leftCell) && (startChecking maxX maxY East cells leftCell)
    | (ct == topRight) && (from == West) && (cx /= maxX) = (connection cCell downCell) && (startChecking maxX maxY North cells downCell)
    | (ct == topRight) && (from == South) && (cx /= 0) = (connection cCell leftCell) && (startChecking maxX maxY East cells leftCell)
    | otherwise = False
        where
            upCell = cells A.! (cx - 1, cy)
            leftCell = cells A.! (cx, cy - 1)
            rightCell = cells A.! (cx, cy + 1)
            downCell = cells A.! (cx + 1, cy)
            cCell = (Cell (cx, cy) ct)

wonLevel :: Level -> Bool
wonLevel (Level _ cells maxX maxY) = startChecking maxX maxY North cells $ head $ filterConnections cells

-- functie care intoarce doar spatiile libere de pe harta
getFreeSpaces:: Level -> [Cell]
getFreeSpaces (Level _ cells _ _) = filter (\(Cell (_, _) t) -> (t == emptySpace)) (A.elems cells)
-- getFreeSpaces (Level _ [] _ _) = []

-- genereaza toate miscariile posibile in jurul unui spatiu liber
genMoves:: Level -> [Cell] -> [((Position, Directions), Level)]
-- genMoves (Level _ [] _ _) _ = []
genMoves (Level _ _ _ _) [] = []
genMoves (Level nr cells dimX dimY) emptyCells = foldl gen [] emptyCells
    where 
        gen list (Cell (cx, cy) _) = list
             ++ (if (cx < dimX) then [(((cx + 1, cy), North), (moveCell (cx + 1, cy) North (Level nr cells dimX dimY)))] else [])
             ++ (if (cy < dimY) then [(((cx, cy + 1), West), (moveCell (cx, cy + 1) West (Level nr cells dimX dimY)))] else [])
             ++ (if (cy > 0) then [(((cx, cy - 1), East), (moveCell (cx, cy - 1) East (Level nr cells dimX dimY)))] else [])
             ++ (if (cx > 0) then [(((cx - 1, cy), South), (moveCell (cx - 1, cy) South (Level nr cells dimX dimY)))] else [])

-- genereaza succesorii nivelului curent
buildSuccessors::  Level -> [((Position, Directions), Level)]
buildSuccessors lvl = filter onlyValid (genMoves lvl (getFreeSpaces lvl))
    where 
        onlyValid (((x, y), _), (Level nrNext _ dimX dimY)) = (nrNext /= nr) && (x >= 0) && (x <= dimX)
            && (y >= 0) && (y <= dimY)
        (Level nr _ _ _) = lvl 

-- inverseaza o actiune
revAction:: ((Position, Directions), Level) -> ((Position, Directions), Level)
revAction (((x, y), dir), lvl)
    | (dir == North) = (((x - 1, y), South), lvl)
    | (dir == South) = (((x + 1, y), North), lvl)
    | (dir == East) = (((x, y + 1), West), lvl)
    | (dir == West) = (((x, y - 1), East), lvl)
    | otherwise = (((x, y), dir), lvl)

instance ProblemState Level (Position, Directions) where
    successors = buildSuccessors
    isGoal = wonLevel
    reverseAction = revAction
