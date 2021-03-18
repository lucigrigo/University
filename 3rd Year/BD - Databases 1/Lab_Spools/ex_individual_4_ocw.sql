accept id_dep char prompt 'Introduceti departamentul angajatului:'
accept min_salariu char prompt 'Introduceti venitul anual minim:'

select nume, id_dep, data_ang, 12*&&venit_lunar venit_anual
from angajati1
where id_dep = &id_dep and 12*&venit_lunar > &min_salariu
order by data_ang;

undefine id_dep
undefine min_salariu
undefine venit_lunar