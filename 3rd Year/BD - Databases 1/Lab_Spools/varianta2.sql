define id_dep=30
define job_name='analyst'

select deptno as ID_dep, ename as Nume_angajat, hiredate as Data_angajare, job as Job, sal+nvl(comm, 0) as Venit_lunar
from emp where (deptno = &id_dep and lower(job) = '&job_name');

undefine id_dep
undefine job_name