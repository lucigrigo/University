{-
  Definirea tipului Punct folosind type
  În acest caz, tipul de date pentru
  perechea care formează punctul trebuie
  definit la creare.
-}

type Punct = (Int, Int)

manhattanDistance :: Punct -> Punct -> Int
manhattanDistance p1 p2 = difX + difY
  where
    difX = abs (x1 - x2)
    difY = abs (y1 - y2)
    (x1, y1) = p1
    (x2, y2) = p2

{-
 - Newtype
 -}

{-
  Definirea tipurilor Celsius și Fahrenheit
  împreună cu funcțiile de conversie
-}

newtype Celsius = MakeCelsius Float deriving Show

newtype Fahrenheit = MakeFahrenheit Float deriving Show

fah2cel :: Fahrenheit -> Celsius
fah2cel (MakeFahrenheit x) = MakeCelsius ((5 / 9) * (x - 32))

cel2fah :: Celsius -> Fahrenheit
cel2fah (MakeCelsius x) = MakeFahrenheit (x * 9 / 5 + 32)

{-
  Se observă că, pentru a defini funcțiile de conversie,
  se descompune tipul de date primit. În primul caz,
  elementul de tip Fahrenheit se descompune în MakeFahrenheit x
  și se folosește valoarea x în calcule, urmând ca valoarea
  calculată pentru celsius să fie pasată constructorului
  MakeCelsius, funcția având ca rezultat un element de tip
  Celsius
-}

{-
  newtype poate fi parametrizat, însa constructorul său primește
  un singur parametru. Așa că, în construirea tipului Pair folosind
  newtype și tipurile a și b, constructorul primește un singur
  argument, o pereche de tipurile a și b
-}
newtype PairT a b = PairC (a,b) deriving Show

fstPair (PairC p) = fst p
sndPair (PairC p) = snd p


{-
 - Data
 -}

{-
  Tipuri înregistrare
-}

{-
  Folosirea tipurilor înregistrare.
  Având tipul de date Student cu constructorul Student,
  care primește 3 parametri String String Int, definit
  ca tip înregistrare se poate observa utilizarea
  funcțiilor de extracție a datelor definite drept
  câmpuri ale tipului
-}

data Student = Student { nume :: String
             , prenume :: String
             , varsta :: Int
             } deriving Show
{-
  Pentru a folosi o instanță de tipul Student,
  aceasta se poate construi prin furnizarea datelor de tipurile
  corespunzătoare constructorului
  În consola ghci se rulează:
   :t nume
   :t prenume
   :t varsta
   nume (Student "Ion" "Ionut" 23)
   prenume (Student "Ion" "Ionut" 23)
   varsta (Student "Ion" "Ionut" 23)
-}

{-
  Tipuri enumerare
-}

data Zi = Luni | Marti | Miercuri | Joi | Vineri | Sambata | Duminica deriving Show

nrCeasuriRele zi = case zi of
          Marti -> 3
          otherwise -> 0


{-
  Tipuri parametrizate
-}

data Vector a = Vector a a a deriving Show

vectPlus :: (Num a) => Vector a -> Vector a -> Vector a
vectPlus (Vector x y z) (Vector i j k) = Vector (x + i) (y + j) (k + z)

scalarMult :: (Num a) => Vector a -> a -> Vector a
scalarMult (Vector x y z) m = Vector (x * m) (y * m) (z * m)


{-
  În unele cazuri, se dorește anunțarea unui eșec în evaluarea
  funcției. Pentru acest lucru există Maybe.
-}

-- data Maybe a = Just a | Nothing deriving Show

{-
  Tipul Maybe a reprezintă tipul rezultatului evaluării, acesta
  fiind Just a, în cazul în care evaluarea s-a efectuat cu succes
  sau Nothing în caz contrar. De reținut că a este o variabila de tip
  și în cazul întoarcerii cu succes Just va fi acompaniat de valoarea
  ce are tipul a
-}

{-
  Funcția myHead va returna Nothing în cazul în care lista este vidă și
  încercarea de a obține capul listei nu se poate realiza. În cazul în care
  lista conține cel puțin un element se întoarce Just x
-}
myHead [] = Nothing
myHead (x:_) = Just x

{-
  În cazul în care se doresc rezultatele unor funcții care întorc Maybe
  pentru a le utiliza se poate proceda folosind pattern match sau case
-}

sumHeadLists fstList sndList = case myHead fstList of
                Nothing -> Nothing
                Just x -> case myHead sndList of
                      Nothing -> Nothing
                      Just y -> Just (x + y)

{-
  Tipuri de date recursive
-}

{-
  Tipul numerelor naturale definit recursiv.
  Ex: numărul 0 este Zero iar celelalte vor fi
  aplicări ale constructorului Succ asupra lui Zero
-}

data Natural = Zero | Succ Natural deriving Show

-- Pentru a trece un număr natural în Natural se fac apeluri recursive până la 0
toNatural :: Int -> Natural
toNatural 0 = Zero
toNatural x = Succ (toNatural $ x - 1)

-- Pentru a trece un Natural în număr natural se fac apeluri recursive până la Zero
toInt :: Natural -> Int
toInt Zero = 0
toInt (Succ x) = 1 + (toInt x)


{-
  Pentru a declara tipul de date arbore binar de tipul a în care valorile sunt
  ținute în frunze:
-}

data BinaryTree a = Node (BinaryTree a) (BinaryTree a) | Leaf a deriving Show

{-
  makeTree primește o listă de numere și va întoarce arborele binar cu numerele
  respective în frunze

  În cazul în care se trimite o listă vidă va da eșec, întrucât tipul nu
  permite un arbore vid
-}

makeBinTree :: [a] -> BinaryTree a
makeBinTree lst = head $ mergeUpwards leafList
    where
      leafList = map (\x -> Leaf x) lst
      mergeUpwards [] = []
      mergeUpwards [x] = [x]
      mergeUpwards (x:y:xs) = mergeUpwards ( (Node x y) : mergeUpwards xs)

{-
 - Tipul de date list
 -}

{-
  Tipul de date TList reprezinta tipul listă reprezentativ
  pentru limbaje funcționale. Este format din constructorul Nil pentru
  terminarea listei și constructorul de concatenare.
-}
data TList a = Cons a (TList a) | Nil deriving Show

{-
  tlistToList transformă o TList într-o listă Haskell
-}
tlistToList :: TList a -> [a]
tlistToList Nil = []
tlistToList (Cons x y) = x : tlistToList y

{-
  listToTList transformă o listă Haskell într-o listă TList
-}
listToTList :: [a] -> TList a
listToTList [] = Nil
listToTList (x:xs) = Cons x (listToTList xs)

