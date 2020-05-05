{-# LANGUAGE MultiParamTypeClasses, FunctionalDependencies,
  FlexibleContexts, InstanceSigs #-}

module AStarHeuristic where
import RollTheBall
import ProblemState

import Data.Hashable
import Data.Graph.AStar
import qualified Data.HashSet as H

{-
	Semnătura lui aStar este:
		aStar 	:: (Hashable a, Ord a, Ord c, Num c)
			=> (a -> HashSet a)
			-> (a -> a -> c)
			-> (a -> c)
			-> (a -> Bool)
			-> a
			-> Maybe [a], a fiind tipul Level.
	Vom discuta mai jos despre fiecare parametru în parte.
-}

{-
 	*** TODO ***
	
	O constrângere pe care trebuie să o îndeplinească Level pentru a apela
	AStar pe graful nostru este ca Level să fie instanță a lui Hashable.
	Pentru a face asta, trebuie să definim funcția hashWithSalt. Aceasta
	va primi un Int, Level-ul nostru și va returna un Int, adica hash-ul
	rezultat.

	Hint: Dacă un tip de dată 'a' este instanță de Hashable, atunci și
	'[a]' este. Pe considerentul acesta, o sugestie ar fi de defini o
	funcție care extrage din reprezentarea lui Level, Cells sub formă de
	listă sau lista de liste. Următorul pas ar fi să instanțiem Cell pe
	Hashable. Char este, de asemenea, instanța Hashable.

	În cazul acesta,  avem

	    hashWithSalt i level = hashWithSalt i $ toList level
 -}
levelToList :: Level -> [Cell]
levelToList = undefined

instance Hashable Cell where
	hashWithSalt :: Int -> Cell -> Int
	hashWithSalt = undefined

instance Hashable Level where
	hashWithSalt :: Int -> Level -> Int
	hashWithSalt = undefined
{-
	*** TODO ***
	
	Primul parametru al lui aStar ne va returna graf-ul pe care îl
	parcurgem. Acesta este sub forma unei funcții care primește drept
	parametru un nod, aici un Level, și întoarce vecinii săi, sub formă de
	HashSet.

	Hint: fromList
-}

neighbours :: (Level -> H.HashSet Level)
neighbours = undefined

{-
 	*** TODO ***

	Urmează distanța dintre noduri. Aceasta este o funcție care primește
	două elemente de tip Level și întoarce un număr care reprezintă
	distanța dintre ele.

	Atenție! Aceasta va fi apelată doar pe nivele adiacente!
 -}
 
distance :: (Num c) => (Level -> Level -> c)
distance = undefined 

{-
	Urmează euristica folosită.

	Primul apel pe aStar va fi folosind o euristică banală, care întoarce 1,
	indiferent ne nivel.
-}
trivialHeuristic :: (Num a) => Level -> a
trivialHeuristic _ = 1

{-
	*** TODO ***
	
	Dacă există, aStar returnează un drum optim de către nodul final,
	excluzând nodul de început.
-}
nonTrivialHeuristic :: (Num c) => Level -> c
nonTrivialHeuristic = undefined

{-
 	*** TODO ***

	Penultimul parametru este o funcție care verifică dacă nodul curent
	este final, sau nu.
 -}
isGoalNode :: Level -> Bool
isGoalNode = undefined 

{-
 	Ultimul parametru dat lui aStar reprezintă nodul de la care se
	începe căutarea.

	Dacă există, aStar returnează un drum optim de către nodul final,
	excluzând nodul de început.
-}
