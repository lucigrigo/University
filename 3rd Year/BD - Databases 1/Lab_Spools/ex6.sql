accept functie_ang char prompt 'Introduceti functia angajatului:'

select nume, salariu, comision
from angajati1
where functie = '&functie_ang';

undefine functie_ang