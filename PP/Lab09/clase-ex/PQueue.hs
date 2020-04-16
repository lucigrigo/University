{-# LANGUAGE MultiParamTypeClasses #-}
{-# LANGUAGE FlexibleInstances #-}

module PQueue where

import Data.Maybe
import Data.List (sort)
import TestPP

{-
    Următoarele exerciții vor avea drept scop implementarea unei mici biblioteci
    pentru o coadă de priorități (mai specific, un max priority queue - "primul" element
    are prioritatea cea mai mare).
    Coada de priorități va fi reprezentată folosind o listă sau un arbore binar.
    Biblioteca noastră va defini o reprezentare generală pentru coada de priorități,
    precum și funcții care operează pe aceasta.
-}

 ----------------------------------------------------------------------------------------------------
{- Setup Testare -}

valsInt = [20, 100, 30, 500, 1000, 30023, 513]
valsStr = ["PP", "PA", "PC", "AA", "LFA", "IA", "ML"]
prios = [5, 2, 10, -3, 1, 20]
elemsInt = zip prios valsInt
elemsStr = zip prios valsStr

-- Considerăm că un element din coadă este reprezentat de un tuplu care va conține:
-- * prioritatea
-- * valoarea
type Prio = Int

{-
    1.(1.5p) Analizați clasa PQueue definită mai jos și scrieți implementările
    implicite pentru funcțiile din această clasă:
    * fromList
    * toList

    Clasa PQueue definește interfața pentru toate structurile de coadă de priorități
    pe care le vom implementa mai jos.
-}

class (Ord a) => PQueue pq a where

    -- Construiește o coadă de priorități goală
    empty :: pq a

    -- Verifică dacă coada este goală
    isEmpty :: pq a -> Bool

    -- Inserează un element în coada de priorități
    insert :: (Prio, a) -> pq a -> pq a

    -- Întoarce primul element din coada de priorități
    top :: pq a -> Maybe (Prio, a)

    -- Șterge primul element din coada de priorități
    -- Dacă coada nu are elemente se va returna coada goală
    pop :: pq a -> pq a
    
    -- Creează o coadă de priorități dintr-o lista de tupluri
    -- Elementele vor fi adăugate în ordine inversă (de la finalul spre începutul listei)
    fromList :: [(Prio, a)] -> pq a
    fromList = undefined

    toList :: pq a -> [(Prio, a)]
    toList = undefined

    size :: pq a -> Int
    size = undefined -- Pentru Ex 6

test1OK = False

-- Test 1

check1 :: TestData
check1 = test 1 $ testManually "Priority Queue Class" 1.5 test1OK -- 1.5p

-------------------------------------------------------------------------------

{-
    2.(2.0p) Definiți tipul ListPQ care reprezintă o coadă de priorități ca pe o
    listă de elemente. Includeți ListPQ în clasa PQueue.
-}

newtype ListPQ a = LPQ a deriving Show

instance (Ord a) => PQueue ListPQ a where
    empty = undefined

    insert = undefined

    top = undefined

    pop = undefined

    isEmpty = undefined

-- Test 2

listPQInt :: ListPQ Int
listPQInt = fromList elemsInt

listPQStr :: ListPQ String
listPQStr = fromList elemsStr

check2 :: TestData
check2 = tests 2 2.0 -- 2.0p
            [
              testVal "ListPQ Int check" 1.5 (reverse $ sort elemsInt) $ toList listPQInt,
              testVal "ListPQ Str check" 1.5 (reverse $ sort elemsStr) $ toList listPQStr
            ]

{-
    LeftistPQ reprezintă o coadă de priorități ca pe un arbore binar.
    Un nod din LeftistPQ conține următoarele informații:
	 * Rang-ul (îl veți mai găsi sub denumirea de npl - null path length) unui nod X reprezintă
        lungimea cea mai scurtă de la acest nod la un nod fără 2 copii
	   * Rang-ul unui nod Empty este 0
	 * Un tuplu care reprezintă (prioritatea din nod, valoarea din nod)
     * Subarborele stânga și dreapta

    Referință - pentru mai multe detalii despre construcție: http://typeocaml.com/2015/03/12/heap-leftist-tree/  
    Vizualizare: https://www.cs.usfca.edu/~galles/visualization/LeftistHeap.html
-}

type Rank = Int

data LeftistPQ a = Empty { rank :: Rank } |
                   Node { rank :: Rank, nodeVal :: (Prio, a), left :: LeftistPQ a, right :: LeftistPQ a }

{-
    3.(2.5p) Definiți operația de "merge" care primește 2 parametri de tipul LeftistPQ și intoarce
    un nou LeftistPQ obținut prin combinare.
    Cazuri de tratat:
    * Dacă unul dintre noduri este Empty
    * Dacă ambele noduri sunt Empty
    * Dacă nodurile nu sunt Empty
    Trebuie definită și operația inorder pentru parcurgerea arborelui - este folosit la validare

	  Structura arborelui:
	* subarborele stânga va avea întotdeauna rangul mai mare sau egal cu rangul subarborelui dreapta
 
	  Operația de "merge" între 2 noduri care nu sunt Empty va funcționa în modul următor:
	* Se verifică care nod are prioritatea mai mare și acel nod va deveni noua rădăcină
	* Se păstrează subarborele stânga al noii radăcine, iar subarborele drepta va deveni
      rezultatul funcției de "merge" pe subarborele dreapta al rădăcinii și nodul care nu a fost
	  selectat drept rădăcină
	* La întoarcea din recursivitate se "rotesc" copiii, astfel încât subarborele stânga sa aibă rang-ul mai
	  mare sau egal decât cel din dreapta.
-}

merge :: LeftistPQ a -> LeftistPQ a -> LeftistPQ a
merge = undefined

inorder :: LeftistPQ a -> [(Prio, a)]
inorder = undefined

-- Test 3

check3 :: TestData
check3 = tests 3 2.5
          [
            testVal "Inorder Merge Empty NotEmpty" 0.25 [(3,4)] $ inorder $ merge emptyNode node1,
            testVal "Inorder Merge NotEmpty Empty" 0.25 [(3,4)] $ inorder $ merge node1 emptyNode,
            testVal "Inorder Merge NotEmpty NotEmpty" 0.25 [(3,4), (5,10)] $ inorder $ merge node1 node2,
            testVal "Inorder Merge" 0.25 [(3,4), (5,10), (10,20), (4,10)] $ inorder $ merge node4 $ merge node3 $ merge node1 node2
          ]
        where
          emptyNode = Empty 0
          node1 = Node 1 (3, 4) emptyNode emptyNode
          node2 = Node 1 (5, 10) emptyNode emptyNode
          node3 = Node 1 (10, 20) emptyNode emptyNode
          node4 = Node 1 (4, 10) emptyNode emptyNode

          {-
           - Inorder Merge Test:
           - Primul merge:
           -      (5,10)
           -       / \ 
           -      /   \
           -     /     \
           -  (3,4)   ---
           -
           -
           - Al doilea merge:
           -        (10,20)
           -         /  \
           -        /    \
           -       /      \
           -    (5,10)    ---
           -     /
           -    /
           -  (3,4)
           -
           -  Al treilea merge:
           -         (10,20)
           -           /  \
           -          /    \
           -         /      \
           -      (5,10)    (4,10)
           -       /
           -      /
           -     /
           -   (3,4)
           -}
{-
    4.(1.5p) Includeți LeftistPQ în PQueue
-}

instance (Ord a) => PQueue LeftistPQ a where

    empty = undefined

    isEmpty = undefined
    
    insert = undefined

    top = undefined

    pop = undefined

-- Test 4

leftistPQInt :: LeftistPQ Int
leftistPQInt = fromList elemsInt

leftistPQStr :: LeftistPQ String
leftistPQStr = fromList elemsStr

check4 :: TestData
check4 = tests 4 1.5 -- 1.5p
          [
            testVal "LeftistPQ toList" 0.75 (reverse $ sort elemsInt) $ toList leftistPQInt,
            testVal "LeftistPQ toList" 0.75 (reverse $ sort elemsStr) $ toList leftistPQStr
          ]

{-
    5.(1.0p) Definiți funcția convert care face conversia intre cele 2 tipuri de reprezentări
-}

convert :: (PQueue pq1 a, PQueue pq2 a) => pq1 a -> pq2 a
convert = undefined

-- Test 5

check5 :: TestData
check5 = tests 5 1.0 -- 1.0p
          [
            testVal "Convert ListPQInt to LeftistPQInt" 1 (toList listPQInt) $ toList convertedLeftistPQInt,
            testVal "Convert ListPQStr to LeftistPQStr" 1 (toList listPQStr) $ toList convertedLeftistPQStr,
            testVal "Convert LeftistPQInt to ListPQInt" 1 (toList leftistPQInt) $ toList convertedListPQInt,
            testVal "Convert LeftistPQStr to ListPQStr" 1 (toList leftistPQStr) $ toList convertedListPQStr
          ]
        where
          convertedLeftistPQInt :: LeftistPQ Int
          convertedLeftistPQInt = convert listPQInt

          convertedLeftistPQStr :: LeftistPQ String
          convertedLeftistPQStr = convert listPQStr

          convertedListPQInt :: ListPQ Int
          convertedListPQInt = convert leftistPQInt

          convertedListPQStr :: LeftistPQ String
          convertedListPQStr = convert leftistPQStr


{-
    6.(1.5p) Adăugați o nouă funcție "size" în clasa PQueue care întoarce numărul de elemente din coadă
    Atenție: Trebuie să fie definită implicit în PQueue
-}

-- Test 6

check6 :: TestData
check6 = tests 6 1.5 -- 1.5p
          [
            testVal "Size ListPQ Int" 0.5 (size listPQInt) refSize,
            testVal "Size LeftistPQ Int" 0.5 (size leftistPQInt) refSize
          ]
        where
          refSize = length elemsInt

{-
    7.(BONUS 2.0p)  Adăugați tipurile ListPQ și LeftistPQ în clasa MyFoldable
        Funcția f primește drept parametri: o valoare din coadă (al doilea element din tuplu)
    și acumulatorul.
        Pentru ListPQ foldr' ar trebui să aibă același comportament ca foldr.
        Pentru LeftistPQ foldr' ar trebui să parcurgă arborele dreapta, rădăcină, stânga.
        

    Reminder:
        :t foldr
        foldr :: (a -> b -> b) -> b -> [a] -> b 

        În Haskell 8.x.x tipul arată în felul următor
        :t foldr
        foldr :: (Foldable t) => (a -> b -> b) -> b -> t a -> b

        Clasa Foldable caracterizează tipurile care pot fi "reduse" la o anumită valoare utilizând operații specifice (foldr, foldl).
        Foldable t este o constrângere de tip, iar "t a" este un container care conține valori de tipul a.

        Mai multe informații: https://wiki.haskell.org/Foldable_and_Traversable
-}

-- Dacă doriți, puteți modifica contextul tipului lui foldr'
class MyFoldable f where
    foldr' :: (a -> b -> b) -> b -> f a -> b

instance MyFoldable ListPQ where
    foldr' = undefined

instance MyFoldable LeftistPQ where
    foldr' = undefined

-- Test 7

check7 :: TestData
check7 = tests 7 2.0 -- 2.0p
          [
            testVal "MyFoldable ListPQ Int" 0.5 0 $ foldr' fInt 0 listPQInt,
            testVal "MyFoldable ListPQ Str" 0.5 "IAPCPPPALFAAA" $ foldr' fStr "" listPQStr,
            testVal "MyFoldable LeftistPQ Int" 0.5 0 $ foldr' fInt 0 leftistPQInt,
            testVal "MyFoldable LeftistPQ Str" 0.5 "AAPCPAIALFAPP" $ foldr' fStr "" leftistPQStr
          ]
        where
          fStr = (++)
          fInt = (*)

          {-
           -     Leftist PQ (Rank, Priority, Value)
           -           (2,        20,     "IA")
           -             /                    \
           -            /                      \
           -           /                        \
           -       (2, 10, "PC")                (1,    5,   "PP")
           -         /        \                     /         \
           -        /          \                   /           \
           -       /            \                 /             \
           -    (1, -3, "AA")   (1, 2, "PA")    (1, 1, "LFA")   ---
           -     /      \            /  \           /  \
           -    /        \          /    \         /    \
           -   /          \        /      \       /      \
           - ---          ---     ---     ---    ---     ---
           -
           -}


{-
    8.(BONUS 1.0p)  Adăugați tipurile ListPQ și LeftistPQ în clasa MyFunctor
       Funcția f primește ca parametru o valoare din coadă (al doilea element din tuplu)
-}

class MyFunctor f where
    fmap' :: (Ord a, Ord b) => ((Prio, a)  -> (Prio, b)) -> f a -> f b

instance MyFunctor ListPQ where
    fmap' = undefined

instance MyFunctor LeftistPQ where
    fmap' = undefined

-- Test 8

check8 :: TestData
check8 = tests 8 1.0 -- 1.0p
          [
            testVal "MyFunctor ListPQ Int" 0.5  refInt $ toList $ fmap' fInt listPQInt,
            testVal "MyFunctor ListPQ Str" 0.5 refStr $ toList $ fmap' fStr listPQStr,
            testVal "MyFunctor LeftistPQ Int" 0.5  refInt $ toList $ fmap' fInt leftistPQInt,
            testVal "MyFunctor LeftistPQ Str" 0.5 refStr $ toList $ fmap' fStr leftistPQStr
          ]
        where
          fInt (x, y) = (x - 10, y + 100)
          fStr (x, y) = (x + 10, y ++ "42")

          refInt = reverse $ sort $ map fInt elemsInt
          refStr = reverse $ sort $ map fStr elemsStr

{-
    9.(BONUS 2.0p) Adăugați LeftistPQ în clasa Show
    Va trebui ca arborele să fie afișat în modul următor:
    "--" x nivel în arbore {valoare din nod}
    Dacă nodul este Empty atunci se va afișa în loc de {valoare din nod} "empty"
    Ex: Node _ (3,4) {Node _ (4,5) Empty Empty} {Node _ (5,6) {Node _ (6,7) Empty Empty} Empty} -- nu ne interesează rankul
    --(3,4)
    ----(4,5)
    ------empty
    ------empty
    ----(5,6)
    ------(6,7)
    --------empty
    --------empty
    ------empty <-- și aici este newline la final

    Hint: Parcurgere preordine
-}

instance (Show a) => Show (LeftistPQ a) where
    show = undefined

-- Test 9

check9 :: TestData
check9 = tests 9 2.0 -- 2.0p
          [
            testVal "Show LeftistPQ Str" 1.0 refLeftistPQStr $ show leftistPQStr,
            testVal "Show LeftistPQ Int" 1.0 refLeftistPQInt $ show leftistPQInt
          ]
        where
          refLeftistPQStr = "--(20,\"IA\")\n\
                           \----(10,\"PC\")\n\
                           \------(-3,\"AA\")\n\
                           \--------empty\n\
                           \--------empty\n\
                           \------(2,\"PA\")\n\
                           \--------empty\n\
                           \--------empty\n\
                           \----(5,\"PP\")\n\
                           \------(1,\"LFA\")\n\
                           \--------empty\n\
                           \--------empty\n\
                           \------empty\n"

          refLeftistPQInt = "--(20,30023)\n\
                           \----(10,30)\n\
                           \------(-3,500)\n\
                           \--------empty\n\
                           \--------empty\n\
                           \------(2,100)\n\
                           \--------empty\n\
                           \--------empty\n\
                           \----(5,20)\n\
                           \------(1,1000)\n\
                           \--------empty\n\
                           \--------empty\n\
                           \------empty\n"

check = quickCheck [check1, check2, check3, check4, check5, check6, check7, check8, check9]
