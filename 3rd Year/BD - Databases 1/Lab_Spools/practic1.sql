accept venit_anual_minim char prompt "Introduceti venitul anual minim: "
accept ultima_litera char prompt "Introduceti ultima litera: "
select ENAME||' cu functia '||JOB AS "Info angajati", 12*(sal+nvl(comm,0)) AS "Venit anual" FROM EMP WHERE 12*(sal+nvl(comm,0)) > &venit_anual_minim AND ENAME NOT LIKE '%&ultima_litera'
undefine venit_anual_minim
undefine ultima_litera