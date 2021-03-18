define tabela=angajati1
define id_sef=7698
define data_ang_sef=01-JAN-1920

select nume Nume, data_ang Data_angajare, functie Job, id_sef Ecuson_sef
from &tabela
where id_sef = &id_sef and data_ang > '&data_ang_sef';

undefine tabela
undefine id_sef
undefine data_ang_sef