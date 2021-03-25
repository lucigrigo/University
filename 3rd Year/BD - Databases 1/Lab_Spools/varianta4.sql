select deptno as ID_dep, ename as Nume_angajat, hiredate as Data_angajare, job as Job, &venit_lunar as Venit_lunar
from emp where (deptno = &1 and lower(job) = '&2');