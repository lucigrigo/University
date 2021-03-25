accept id_dep char prompt "Introduceti id-ul departamentului:"
accept job_name char prompt "Introduceti numele functiei:"

select deptno as ID_dep, ename as Nume_angajat, hiredate as Data_angajare, job as Job, &venit_lunar as Venit_lunar
from emp where (deptno = &id_dep and lower(job) = '&job_name');

undefine id_dep
undefine job_name