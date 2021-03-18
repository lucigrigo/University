accept id_ang char prompt 'Introduceti ecusonul angajatului:'
accept nume char prompt 'Introduceti numele angajatului:'
accept functie char prompt 'Introduceti functia angajatului:'
accept salariu char prompt 'Introduceti salariul angajatului:' hide

insert into angajati1(id_ang, nume, functie, salariu)
values(&id_ang, '&nume', '&functie', &salariu);

undefine id_ang
undefine functie
undefine nume
undefine salariu