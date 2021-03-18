select nume Nume, data_ang Data_angajare, functie Job, id_sef Ecuson_sef
from angajati1
where id_sef = &id_sef and data_ang > '&data_ang_sef';