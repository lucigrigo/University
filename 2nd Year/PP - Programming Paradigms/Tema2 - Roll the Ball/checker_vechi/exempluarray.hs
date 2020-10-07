{--
Pentru a înțelege mai bine cum funcționează Data.Array puteți urmări
următorul exemplu de definire pentru urmatoarea matrice. 
1 2 
3 4 
Constructorul pentru un array este 'array' și are ca prim parametru o
pereche cu indexul minim și indexul maxim. 
În cazul nostru un index va avea tipul (Int, Int)', iar coltul din dreapta
jos va avea indexul (1, 1).
--}
import Data.Array as A

arr::(A.Array (Int, Int) Int)
arr = A.array ((0, 0), (1, 1)) 
              [((0, 0), 1), ((0, 1), 2),
               ((1, 0), 3), ((1, 1), 4)]

{--
Doi operatori utili sunt // și !. Funcționalitatea lor este expusă în
exemplele de mai jos.
--}

updateArr :: (A.Array (Int, Int) Int) -> (A.Array (Int, Int) Int)
updateArr arr = arr A.// [((1,i), 5) | i <- [0, 1]]
{-- Aplicat pe array-ul definit anterior vom obtine matricea:
1 2
5 5
Astfel ca se va umple linia 1 cu valoarea 5.
--}

--Comanda 'arr A.! (x, y)' va întoarce elementul de pe linia x și coloana y.
elemAt :: (A.Array (Int, Int) Int) -> (Int, Int) -> Int
elemAt arr pos = arr A.! pos
{--
Însă pentru arr definit anterior, 'arr A.! (2, 1)' va genera o eroare:
'Exception: Error in array index'. Doarece indexul 
--}

{-- 
Pentru a lucra efectiv cu elementele array-ului se poate folosi functia elems.
Urmatoarea functie va intoarce elementele matricei arr definita mai sus:
[1, 2, 3, 4]
--}
elemsList :: [Int]
elemsList = A.elems arr

{-- 
Indexul minim si maxim al unui array se obtin folosind functia 'bounds'.
In cazul nostru un exemplu util ar fi sa obtinem coordonatele coltului din
stanga jos.
lowerRightCorner arr ==> (1,1)
--}
lowerRightCorner :: (A.Array (Int, Int) Int) -> (Int, Int)
lowerRightCorner = snd . A.bounds

{--
Pentru mai multe informatii puteti sa investigati documentatia modulului.
http://hackage.haskell.org/package/array-0.5.3.0/docs/Data-Array.html
--}
