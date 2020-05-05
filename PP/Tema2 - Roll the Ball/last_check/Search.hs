{-# OPTIONS_GHC -Wall #-}
{-# LANGUAGE MultiParamTypeClasses #-}

module Search where
import ProblemState
import Data.Maybe

{-
    *** TODO ***

    Tipul unei nod utilizat în procesul de căutare. Recomandăm reținerea unor
    informații legate de:

    * stare;
    * acțiunea care a condus la această stare;
    * nodul părinte, prin explorarea căruia a fost obținut nodul curent;
    * adâncime
    * copiii, ce vor desemna stările învecinate
-}

data Node s a = Node s (Maybe a) (Maybe (Node s a)) Int [Node s a]
    deriving (Eq, Ord)

{-
    *** TODO ***
    Gettere folosite pentru accesul la câmpurile nodului
-}

nodeState :: Node s a -> s
nodeState (Node state _ _ _ _) = state

nodeParent :: Node s a -> Maybe (Node s a)
nodeParent (Node _ _ parent _ _) = parent

nodeDepth :: Node s a -> Int
nodeDepth (Node _ _ _ depth _) = depth

nodeAction :: Node s a -> Maybe a
nodeAction (Node _ action _ _ _) = action

nodeChildren :: Node s a -> [Node s a]
nodeChildren (Node _ _ _ _ children) = children

{-
    *** TODO ***

    Generarea întregului spațiu al stărilor
    Primește starea inițială și creează nodul corespunzător acestei stări,
    având drept copii nodurile succesorilor stării curente.
-}

-- functie care creeaza un nod nou
createNode:: (ProblemState s a, Eq s) => s -> Maybe a -> Maybe (Node s a) -> Int -> Node s a
createNode state action parent depth = current
    where
        current = Node state action parent depth children
        succs = successors state
        children = filter (\(Node s _ _ _ _) -> s /= state) $ map f succs
        f (a, s) = createNode s (Just a) (Just current) (depth + 1)

-- functie care creeaza spatiul starilor
createStateSpace :: (ProblemState s a, Eq s) => s -> Node s a
createStateSpace state = createNode state Nothing Nothing 0

{-
    *** TODO ***
   
    Primește un nod inițial și întoarce un flux de perechi formate din:
    * lista nodurilor adăugate în frontieră la pasul curent
    * frontiera
-}

-- functie care executa un pas din bfs
buildBFS:: (Eq s) => ([Node s a ], [Node s a]) -> [s] -> [([Node s a ], [Node s a])]
buildBFS (_, []) _ = [([], [])]
buildBFS prev@(_, lst) visited = [prev] ++ (buildBFS (c, (tail lst) ++ c) newVisited)
    where
        c = filter (\(Node s _ _ _ _) -> not (elem s visited)) (nodeChildren (head lst))
        cStates = map (\(Node s _ _ _ _) -> s) c
        newVisited = visited ++ cStates

-- functie care face parcurgerea in latime
bfs :: Ord s => Node s a -> [([Node s a], [Node s a])]
bfs start@(Node state _ _ _ _) = buildBFS ([start], [start]) [state]

{-
    *** TODO ***
  
    Primește starea inițială și finală și întoarce o pereche de noduri, reprezentând
    intersecția dintre cele două frontiere.
-}

-- functie care verifica daca doua multimi de noduri au cel putin un element comun
hasInt:: (ProblemState s a, Eq s, Eq a) => [Node s a] -> [Node s a] -> Bool
hasInt f1 f2 = 0 < length (filter (\x -> elem (nodeState x) (map nodeState f1)) f2)

-- functie care genereaza un tuplu de elemente cu stare comuna din doua liste
genInt:: (ProblemState s a, Eq s) => [Node s a] -> [Node s a] -> (Node s a, Node s a)
genInt f1 f2 = (a, b)
    where
        a = head (filter (\x -> elem (nodeState x) (map nodeState f2)) f1)
        b = head (filter (\x -> (nodeState x) == (nodeState a)) f2)

-- functie care gaseste intersectia dintre cele 2 parcurgeri bfs
findIntersection:: (ProblemState s a, Eq a, Eq s, Ord a, Ord s) => 
    [([Node s a], [Node s a])] -> [([Node s a ], [Node s a])] -> (Node s a, Node s a)
findIntersection f1 f2
    | hasInt (fst (head f1)) (snd (head f2)) = genInt (fst (head f1)) (snd (head f2))
    | hasInt (fst (head f2)) (snd (head f1)) = genInt (fst (head f2)) (snd (head f1))
    | otherwise = findIntersection (tail f1) (tail f2)

-- functie care realizeaza cele doua parcurgeri bfs
bidirBFS :: (ProblemState s a, Eq a, Eq s, Ord a, Ord s) => Node s a -> Node s a -> 
    (Node s a, Node s a)
bidirBFS start finish = findIntersection f1 f2
    where
        f1 = bfs start
        f2 = bfs finish

{-
    *** TODO ***

    Pornind de la un nod, reface calea către nodul inițial, urmând legăturile
    către părinți.

    Întoarce o listă de perechi (acțiune, stare), care pornește de la starea inițială
    și se încheie în starea finală.

-}

-- functie care extrage modul de ajungere la un nod din parinte in parinte
extractPath :: Node s a -> [(Maybe a, s)]
extractPath nod = map (\x -> (((nodeAction x)), (nodeState x))) nodes
    where
        nodes = reverse (take ((nodeDepth nod) + 1) (iterate (\x -> (fromJust (nodeParent x))) nod))

{-
    *** TODO ***

    Pornind de la o stare inițială și una finală, se folosește de bidirBFS pentru a găsi
    intersecția dintre cele două frontiere și de extractPath pentru a genera calea.

    Atenție: Pentru calea gasită în a doua parcurgere, trebuie să aveți grijă la a asocia
    corect fiecare stare cu acțiunea care a generat-o.

    Întoarce o listă de perechi (acțiune, stare), care pornește de la starea inițială
    și se încheie în starea finală.
-}

-- functie care realizeaza rezolvarea unui nivel pornind de la nodul de inceput si cel de final
solve :: (ProblemState s a, Eq a, Eq s, Ord a, Ord s)
      => s          -- Starea inițială de la care se pornește
      -> s          -- Starea finală la care se ajunge
      -> [(Maybe a, s)]   -- Lista perechilor
solve start finish = (extractPath directNode) ++ reversePath
    where
        (directNode, reverseNode) = bidirBFS (createStateSpace start) (createStateSpace finish)
        p = reverse (extractPath reverseNode)
        actions =  map fromJust (map fst (init p))
        states =  map snd (tail p)
        reversePath = map (\x -> (Just (fst x), snd x)) (map reverseAction (zip actions states))