select nume Nume, data_ang Data_angajare, functie Job, id_sef Ecuson_sef
from &1
where id_sef = &2 and data_ang > '&3';