accept id_dep char prompt 'Introduceti departamentul angajatului:'
accept min_salariu char prompt 'Introduceti venitul anual minim:'

select nume, id_dep, 12*salariu+nvl(comision,0) venit_anual
from angajati1
where id_dep = &id_dep and &min_salariu < 12*salariu+nvl(comision,0);

undefine id_dep
undefine min_salariu