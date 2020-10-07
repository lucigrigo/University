-- data A = MakeA String deriving (Show, Eq, Ord)
-- data B = MakeB String deriving Show
-- data C = MakeC String deriving (Show, Eq)

-- data DataSet1 = Zero | One deriving (Show, Eq)

-- let x = 7 in [let x = [1..3] in x | x <- [x..10], let x = 5]  
-- f x y = iterate $ x . y
f g (x, y, z) = map g [x, y, z]