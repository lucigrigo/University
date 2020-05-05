{-# OPTIONS_GHC -Wall #-}
{-# LANGUAGE MultiParamTypeClasses, FunctionalDependencies #-}

module ProblemState where

{-
    Expune funcțiile necesare construirii spațiului stărilor, pentru o problemă
    oarecare.

    `s` și `a` reprezintă tipurile stărilor, respectiv acțiunilor
    care transformă o stare în alta.

    Sintaxa `s -> a` din antetul clasei semnifică faptul că `s` îl determină
    în mod unic pe `a`.
-}

class ProblemState s a | s -> a where

    {-
        Pentru starea curentă, furnizează lista perechilor
        (acțiune, stare următoare).
    -}

    successors :: s -> [(a, s)]

    {-
        Întoarce `True` dacă starea curentă este finală.
    -}

    isGoal :: s -> Bool
    {-
        Întoarce acțiunea inversă.
        Exemplu: (South, (1, 0)) -> (North, (2, 0))
    -}

    reverseAction :: (a, s) -> (a, s)

