{-# OPTIONS_GHC -Wall #-}
{-# LANGUAGE EmptyDataDecls, MultiParamTypeClasses,
             TypeSynonymInstances, FlexibleInstances,
             InstanceSigs #-}
module RollTheBall where
import Pipes
import ProblemState
import Data.Array as A

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

-- tipul unei celule
data Cell = Cell Position Char
    deriving (Eq, Ord)

{-
    Tip de date pentru reprezentarea nivelului curent
-}

-- tipul unei clase
data Level = Level (A.Array Position Cell) Int Int
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

-- functie care afiseaza un nivel de celule
fShow:: Level -> String
fShow (Level cells _ dimY) = foldl f [] (A.elems cells) where
    f str (Cell (cx, cy) symbol)
        | (cx == 0) && (cy == 0) = str ++ [endl] ++ [symbol]
        | cy == dimY             = str ++ [symbol] ++ [endl]
        | otherwise              = str ++ [symbol]

-- instanta de Show
instance Show Level 
    where show = fShow

{-
    *** TODO ***
    Primește coordonatele colțului din dreapta jos a hărții.
    Intoarce un obiect de tip Level în care tabla este populată
    cu EmptySpace. Implicit, colțul din stânga sus este (0,0)
-}

-- functie care creeaza un nivel plin de emptySpace
emptyLevel :: Position -> Level
emptyLevel (x, y) = Level (array ((0, 0), (x, y)) [((a, b), 
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

-- functie care adauga o celula
addCell :: (Char, Position) -> Level -> Level
addCell (s, (posX, posY)) (Level cells dimX dimY) 
    | (posX <) 0 || (posY < 0) || (posX > dimX) || (posY > dimY) = (Level cells dimX dimY)
    | (locationType /= emptySpace) = (Level cells dimX dimY)
    | otherwise = (Level (cells A.// [((posX, posY), (Cell (posX, posY) s))]) dimX dimY) 
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
 
-- functie care creeaza un nivel
createLevel :: Position -> [(Char, Position)] -> Level
createLevel (x, y) inputParams = foldr addCell (emptyLevel (x, y)) inputParams

{-
    *** TODO ***

    Mișcarea unei celule în una din cele 4 direcții 
    Schimbul se poate face doar dacă celula vecină e goală (emptySpace).
    Celulele de tip start și win sunt imutabile.

    Hint: Dacă nu se poate face mutarea puteți lăsa nivelul neschimbat.
-}

-- functie care realizeaza mutarea unei celule
moveCell :: Position -> Directions -> Level -> Level
moveCell (x, y) _ (Level cells dimX dimY) 
    | ((cellType == winUp) || (cellType == winDown) || (cellType == winLeft) 
    || (cellType == winRight) || (cellType == startUp) || (cellType == startDown) 
    || (cellType == startLeft) || (cellType == startRight)) || (cellType == emptySpace) = (Level cells dimX dimY)
        where (Cell (_, _) cellType) = cells A.! (x, y)
-- daca se misca in stanga
moveCell (x, y) West (Level cells dimX dimY)
    | y == 0 = (Level cells dimX dimY)
    | (nextType == emptySpace) = (Level (cells A.// [((currX, currY), (Cell (currX, currY) emptySpace)) ,
     ((nextX, nextY), (Cell (nextX, nextY) currType))]) dimX dimY)
    | otherwise = (Level cells dimX dimY)
        where (Cell (currX, currY) currType) = cells A.! (x, y)
              (Cell (nextX, nextY) nextType) = cells A.! (x, y - 1)
-- daca se misca in jos
moveCell (x, y) South (Level cells dimX dimY)
    | (x == dimX) = (Level cells dimX dimY) 
    | (nextType == emptySpace) = (Level (cells A.// [((currX, currY), (Cell (currX, currY) emptySpace)) ,
     ((nextX, nextY), (Cell (nextX, nextY) currType))]) dimX dimY)
    | otherwise = (Level cells dimX dimY)
        where (Cell (currX, currY) currType) = cells A.! (x, y)
              (Cell (nextX, nextY) nextType) = cells A.! (x + 1, y)
-- daca se misca la dreapta
moveCell (x, y) East (Level cells dimX dimY)
    | (y == dimY) = (Level cells dimX dimY)
    | (nextType == emptySpace) = (Level (cells A.// [((currX, currY), (Cell (currX, currY) emptySpace)) , 
    ((nextX, nextY), (Cell (nextX, nextY) currType))]) dimX dimY)
    | otherwise = (Level cells dimX dimY)
        where (Cell (currX, currY) currType) = cells A.! (x, y)
              (Cell (nextX, nextY) nextType) = cells A.! (x, y + 1)
-- daca se misca in sus
moveCell (x, y) North (Level cells dimX dimY) 
    | x == 0 = (Level cells dimX dimY)
    | (nextType == emptySpace) = (Level (cells A.// [((currX, currY), (Cell (currX, currY) emptySpace)) , 
    ((nextX, nextY), (Cell (nextX, nextY) currType))]) dimX dimY)
    | otherwise = (Level cells dimX dimY)
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

-- functie care verifica conexiunea dintre doua celule
connection :: Cell -> Cell -> Bool
connection (Cell (x1, y1) type1) (Cell (x2, y2) type2)
    | (x1 == x2) || (((type1 == winRight) || (type1 == startRight) || (type1 == botLeft) || (type1 == topLeft) || (type1 == horPipe)) 
    || ((type2 == winLeft) || (type2 == startLeft) || (type2 == botRight) || (type2 == topRight) || (type2 == horPipe))) = True 
    | (y1 == y2) || (((type1 == winDown) || (type1 == startDown) || (type1 == topLeft) || (type1 == topRight) || (type1 == verPipe)) 
    || ((type2 == winUp) || (type2 == startUp) || (type2 == botRight) || (type2 == botLeft) || (type2 == verPipe))) = True
    | otherwise = False

{-
    *** TODO ***

    Va returna True dacă jocul este câștigat, False dacă nu.
    Va verifica dacă celulele cu Pipe formează o cale continuă de la celula
    de tip inițial la cea de tip final.
    Este folosită în cadrul Interactive.
-}

-- functie care intoarce doar celula/celulele de start
filterConnections:: (A.Array (Int, Int) Cell) -> [Cell]
filterConnections cells = filter (\(Cell (_, _) t) -> ((t == startDown) || (t == startLeft) || (t == startRight) || (t == startUp))) (A.elems cells)

-- functie recursiva care verifica daca un lant de pipe-uri este conectat
startChecking:: Int -> Int -> Directions -> (A.Array Position Cell) -> Cell -> Bool
startChecking maxX maxY from cells (Cell (cx, cy) ct)
    | (ct == winRight) || (ct == winLeft) || (ct == winUp) || (ct == winDown) = True
    | (ct == startDown) && (cx + 1 <= maxX) && (connection cCell downCell) = (startChecking maxX maxY North cells downCell)
    | (ct == startLeft) && (cy - 1 >= 0) && (connection cCell leftCell) = (startChecking maxX maxY East cells leftCell)
    | (ct == startRight) && (cy + 1 <= maxY) && (connection cCell rightCell) = (startChecking maxX maxY West cells rightCell)
    | (ct == startUp) && (cx - 1 >= 0) && (connection cCell upCell) = (startChecking maxX maxY South cells upCell)
    | (ct == verPipe) && (from == North) && (cx + 1 <= maxX) && (connection cCell downCell) = (startChecking maxX maxY North cells downCell)
    | (ct == verPipe) && (from == South) && (cx - 1 >= 0) && (connection cCell upCell) = (startChecking maxX maxY South cells upCell)
    | (ct == horPipe) && (from == West) && (cy + 1 <= maxY) && (connection cCell rightCell) = (startChecking maxX maxY West cells rightCell)
    | (ct == horPipe) && (from == East) && (cy - 1 >= 0) && (connection cCell leftCell) = (startChecking maxX maxY East cells leftCell)
    | (ct == botLeft) && (from == North) && (cy + 1 <= maxY) && (connection cCell rightCell) = (startChecking maxX maxY West cells rightCell)
    | (ct == botLeft) && (from == East) && (cx - 1 >= 0) && (connection cCell upCell) = (startChecking maxX maxY South cells upCell)
    | (ct == topLeft) && (from == South) && (cy + 1 <= maxY) && (connection cCell rightCell) = (startChecking maxX maxY West cells rightCell)
    | (ct == topLeft) && (from == East) && (cx + 1 <= maxX) && (connection cCell downCell) = (startChecking maxX maxY North cells downCell)
    | (ct == botRight) && (from == West) && (cx - 1 >= 0) && (connection cCell upCell) = (startChecking maxX maxY South cells upCell)
    | (ct == botRight) && (from == North) && (cy - 1 >= 0) && (connection cCell leftCell) = (startChecking maxX maxY East cells leftCell)
    | (ct == topRight) && (from == West) && (cx + 1 <= maxX) && (connection cCell downCell) = (startChecking maxX maxY North cells downCell)
    | (ct == topRight) && (from == South) && (cy - 1 >= 0) && (connection cCell leftCell) = (startChecking maxX maxY East cells leftCell)
    | otherwise = False
        where
            upCell = cells A.! (cx - 1, cy)
            leftCell = cells A.! (cx, cy - 1)
            rightCell = cells A.! (cx, cy + 1)
            downCell = cells A.! (cx + 1, cy)
            cCell = cells A.! (cx, cy)

-- functie care verifica daca un nivel este castigat
wonLevel :: Level -> Bool
wonLevel (Level cells maxX maxY) = startChecking maxX maxY North cells $ head $ filterConnections cells

-- functie care intoarce doar spatiile libere de pe harta
getFreeSpaces:: Level -> [Cell]
getFreeSpaces (Level cells _ _) = filter (\(Cell (_, _) t) -> (t == emptySpace)) (A.elems cells)

-- genereaza toate miscariile posibile in jurul unui spatiu liber
genMoves:: Level -> [Cell] -> [((Position, Directions), Level)]
genMoves (Level _ _ _) [] = []
genMoves (Level cells dimX dimY) emptyCells = foldl gen [] emptyCells
    where 
        gen list (Cell (cx, cy) _) = list
             ++ (if (cx < dimX) then [(((cx + 1, cy), North), (moveCell (cx + 1, cy) North (Level cells dimX dimY)))] else [])
             ++ (if (cy < dimY) then [(((cx, cy + 1), West), (moveCell (cx, cy + 1) West (Level cells dimX dimY)))] else [])
             ++ (if (cy > 0) then [(((cx, cy - 1), East), (moveCell (cx, cy - 1) East (Level cells dimX dimY)))] else [])
             ++ (if (cx > 0) then [(((cx - 1, cy), South), (moveCell (cx - 1, cy) South (Level cells dimX dimY)))] else [])

-- genereaza succesorii nivelului curent
buildSuccessors::  Level -> [((Position, Directions), Level)]
buildSuccessors lvl = filter onlyValid (genMoves lvl (getFreeSpaces lvl))
    where
        onlyValid (((x, y), _), l@(Level _ dimX dimY)) = (lvl /= l) && (x >= 0) && (x <= dimX)
            && (y >= 0) && (y <= dimY)

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
