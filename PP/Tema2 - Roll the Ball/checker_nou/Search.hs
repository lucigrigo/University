{-# OPTIONS_GHC -Wall #-}
{-# LANGUAGE MultiParamTypeClasses #-}

module Search where
import ProblemState
import Data.Maybe

-- import Pipes
-- import RollTheBall

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

showNode:: (ProblemState s a, Show s) => Node s a -> [Char]
showNode (Node s _ _ _ _) = show s

instance (ProblemState s a, Show s) => Show (Node s a)
    where show = showNode

{-
    *** TODO ***

    Generarea întregului spațiu al stărilor
    Primește starea inițială și creează nodul corespunzător acestei stări,
    având drept copii nodurile succesorilor stării curente.
-}

createNode:: (ProblemState s a, Eq s) => s -> Maybe a -> Maybe (Node s a) -> Int -> [s] -> Node s a
createNode state action parent depth visited = current
    where
        current = Node state action parent depth children
        succs = successors state
        children = filter (\(Node s _ _ _ _) -> not (elem s visited)) $ map f succs
        f (a, s) = createNode s (Just a) (Just current) (depth + 1) newVisited
        newVisited = visited ++ [state]

createStateSpace :: (ProblemState s a, Eq s) => s -> Node s a
createStateSpace state = createNode state Nothing Nothing 0 []

{-
    *** TODO ***
   
    Primește un nod inițial și întoarce un flux de perechi formate din:
    * lista nodurilor adăugate în frontieră la pasul curent
    * frontiera
-}

buildBFS:: (Eq s) => ([Node s a ], [Node s a]) -> [s] -> [([Node s a ], [Node s a])]
buildBFS (_, []) _ = []
buildBFS prev@(_, lst) visited = [prev] ++ (buildBFS (c, (tail lst) ++ c) newVisited)
    where
        c = filter (\(Node s _ _ _ _) -> not (elem s visited)) (nodeChildren (head lst))
        cStates = map (\(Node s _ _ _ _) -> s) c
        newVisited = visited ++ cStates

bfs :: Ord s => Node s a -> [([Node s a], [Node s a])]
bfs start@(Node state _ _ _ _) = buildBFS ([start], [start]) [state]

{-
    *** TODO ***
  
    Primește starea inițială și finală și întoarce o pereche de noduri, reprezentând
    intersecția dintre cele două frontiere.
-}

hasInt:: (ProblemState s a, Eq s, Eq a) => [Node s a] -> [Node s a] -> Bool
hasInt f1 f2 = 0 < length (filter (\x -> elem (nodeState x) (map nodeState f1)) f2)

genInt:: (ProblemState s a, Eq s) => [Node s a] -> [Node s a] -> (Node s a, Node s a)
genInt f1 f2 = (a, b)
    where
        a = head (filter (\x -> elem (nodeState x) (map nodeState f2)) f1)
        b = head (filter (\x -> (nodeState x) == (nodeState a)) f2)

findIntersection:: (ProblemState s a, Eq a, Eq s, Ord a, Ord s) => 
    [([Node s a], [Node s a])] -> [([Node s a ], [Node s a])] -> (Node s a, Node s a)
findIntersection f1 f2
    | hasInt (fst (head f1)) (snd (head f2)) = genInt (fst (head f1)) (snd (head f2))
    | hasInt (fst (head f2)) (snd (head f1)) = genInt (fst (head f2)) (snd (head f1))
    | otherwise = findIntersection (tail f1) (tail f2)

    -- | (int1 == []) && (int4 == []) = findIntersection (tail f1) (tail f2)
    -- | (int1 == [])                       = ((head int4), (head (filter (\x -> (nodeState x) == (nodeState (head int4))) (snd (head f1)))))
    -- | otherwise                                  = ((head int1), (head (filter (\x -> (nodeState x) == (nodeState (head int1))) (snd (head f2)))))
    --     where 
    --         -- int1 = filter (\x -> elem (nodeState x) (map nodeState currentStepNodes22)) currentStepNodes11
    --         int1 = filter (\x -> elem (nodeState x) (map nodeState (snd (head f2)))) (fst (head f1))
    --         -- int2 = filter (\x -> elem (nodeState x) $ map nodeState currentStepNodes11) currentStepNodes22
    --         -- int3 = filter (\x -> elem (nodeState x) $ map nodeState currentStepNodes21) currentStepNodes12
    --         -- int4 = filter (\x -> elem (nodeState x) (map nodeState currentStepNodes12)) currentStepNodes21
    --         int4 = filter (\x -> elem (nodeState x) (map nodeState (snd (head f1)))) (fst (head f2))
    --         -- currentStepNodes11 = (fst currentStep1)
    --         -- currentStepNodes12 = (snd currentStep1)
    --         -- currentStepNodes21 = (fst currentStep2)
    --         -- currentStepNodes22 = (snd currentStep2)
    --         -- currentStep1 = (head f1)
    --         -- currentStep2 = (head f2)

bidirBFS :: (ProblemState s a, Eq a, Eq s, Ord a, Ord s) => Node s a -> Node s a -> (Node s a, Node s a)
bidirBFS start finish = undefined --findIntersection f1 f2
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

solve :: (ProblemState s a, Eq a, Eq s, Ord a, Ord s)
      => s          -- Starea inițială de la care se pornește
      -> s          -- Starea finală la care se ajunge
      -> [(Maybe a, s)]   -- Lista perechilor
solve start finish = actions
    where
        directActions = extractPath directNode
        reverseActions = map (\x -> (fromJust (reverseAction (fromJust x)))) (extractPath reverseNode)
        (directNode, reverseNode) = bidirBFS (createStateSpace start) (createStateSpace finish)
        actions = directActions ++ reverseActions
