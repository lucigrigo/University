{-# OPTIONS_GHC -Wall #-}
{-# LANGUAGE EmptyDataDecls, MultiParamTypeClasses,
             TypeSynonymInstances, FlexibleInstances,
             InstanceSigs #-}

module Pipes where
{--
	Acest modul furnizeaza caracterele speciale
    pentru afisarea celulelor nivelului.
--}

horPipe :: Char
horPipe = '═'

verPipe :: Char
verPipe = '║'

topLeft :: Char
topLeft = '╔'

botLeft :: Char
botLeft = '╚'

botRight :: Char
botRight = '╝'

topRight :: Char
topRight = '╗'

emptySpace :: Char
emptySpace =  '░'

emptyCell :: Char
emptyCell = '▓'

startUp :: Char
startUp = '┴'

startDown :: Char
startDown = '┬'

startLeft :: Char
startLeft = '┤'

startRight :: Char
startRight = '├'

winUp :: Char
winUp = '╨'

winDown :: Char--
winDown = '╥'

winLeft :: Char
winLeft = '╡'

winRight :: Char
winRight = '╞'

endl :: Char
endl = '\n'

startCells :: [Char]
startCells = [startUp, startDown, startLeft, startRight]

winningCells :: [Char]
winningCells = [winUp, winDown, winLeft, winRight]
