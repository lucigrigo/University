{-# LANGUAGE GeneralizedNewtypeDeriving #-}
{-# LANGUAGE UndecidableInstances #-}
{-# LANGUAGE MultiParamTypeClasses #-}
{-# LANGUAGE FunctionalDependencies #-}
{-# LANGUAGE FlexibleInstances #-}

{-
    Problema urmărește reprezentarea arborilor ȘI-SAU și operații de bază asupra
    acestora.
    
    Un arbore ȘI-SAU este un arbore următoarele caracteristici:
    * nodurile care nu sunt frunze sunt de tipul ȘI (AND) sau de tipul SAU (OR)
        și pot avea oricâți copii.
    * orice nod este o etichetă care poate fi SUCCESS, FAILURE, sau UNKNOWN.
-}

{-
    (a) (10p) Elaborați reprezentarea arborilor ȘI-SAU. La nevoie, puteți
     utiliza și alte tipuri auxiliare
-}

data NodeOp = AND | OR
    deriving (Eq, Show)

data LeafValue = SUCCESS | FAILURE | UNKNOWN 
    deriving (Eq, Show)

data AndOrTree = Leaf LeafValue | Node LeafValue NodeOp [AndOrTree]
    deriving(Eq)

{-
    (b) (10p) Instanțiați clasa Show cu tipul AndOrTree. Reprezentarea sub
     formă de șir a unui arbore va fi de forma următoare, în care frunzele sunt
     reprezentate prin eticheta lor, iar nodurile ȘI și SAU sunt reprezentate
     prin tipul și eticheta lor:
    (OR|UNKNOWN (AND|UNKNOWN FAILURE (OR|UNKNOWN UNKNOWN SUCCESS) SUCCESS)
      (AND|UNKNOWN SUCCESS (OR|UNKNOWN FAILURE SUCCESS)))
-}
instance Show AndOrTree where
    show (Leaf v) = show v ++ " "
    show (Node v o []) = "(" ++ show o ++ "|" ++ show v ++ ") "
    show (Node v o l) = "(" ++ show o ++ "|" ++ show v ++ " " ++ show l ++ ")"

{-
    (c) (10p) Implementați funcția compute care primește un arbore ȘI-SAU și
     produce un arbore ȘI-SAU în care au fost calculate etichetele pentru
     noduri, după regulile:
    * un nod ȘI are eticheta SUCCESS dacă toți copiii au eticheta SUCCESS,
     altfel FAILURE.
    * un nod SAU are eticheta SUCCESS dacă cel puțin un copil are eticheta
     SUCCESS, altfel FAILURE.
    * toate frunzele rămân nemodificate.
    
    De exemplu, pentru arborele reprezentat ca în exemplul de la punctul (b),
     rezultatul funcției compute este afișat ca:
    (OR|SUCCESS (AND|FAILURE FAILURE (OR|SUCCESS UNKNOWN SUCCESS) SUCCESS)
     (AND|SUCCESS SUCCESS (OR|SUCCESS FAILURE SUCCESS)))
-}
value:: AndOrTree -> LeafValue
value (Leaf v) = v
value (Node v _ _) = v

compute :: AndOrTree -> AndOrTree
compute (Leaf v) = Leaf v
compute (Node v o []) = Node v o []
compute (Node v AND l)
    | (length l) == length (filter (\x -> (value x) == SUCCESS) L) = Node v SUCCESS l
    | otherwise = (Node v FAILURE l)
    where
        L = map compute l
compute (Node v OR l)
    | 0 == length $ filter (\x -> (value x) == SUCCESS) L = (Node v FAILURE l) 
    | otherwise = (Node v SUCCESS l)
    where
        L = map compute l