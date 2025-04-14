--PART1 -------------------------------------------------------------------------------------------------------------------

--1. 문제) 부서번호가 10번인 부서의 사람 중 사원번호, 이름, 월급을 출력하라
--select empno, ename, sal from emp where emp.deptno = 10;

--2. 문제) 사원번호가 7369인 사람 중 이름, 입사일, 부서번호를 출력하라.
--select ename, datetime, deptno from emp where emp.empno = 7369;

--3. 문제) 이름이 ALLEN인 사람의 모든 정보를 출력하라.
--select * from emp where emp.ename = 'ALLEN';

--4. 문제) 입사일이 83/01/12인 사원의 이름, 부서번호, 월급을 출력하라.
--select ename, deptno, sal from emp where emp.datetime = CONVERT(DATETIME, '1981-06-09');

--5. 문제) 직업이 MANAGER가 아닌 사람의 모든 정보를 출력하라.
--select * from emp where not emp.job = 'MANAGER';

--6. 문제) 입사일이 81/04/02 이후에 입사한 사원의 정보를 출력하라.
--select * from emp where emp.datetime > CONVERT(DATETIME, '1981-04-02');

--7. 문제) 급여가 $800 이상인 사람의 이름, 급여, 부서번호를 출력하라.
--select ename, sal, deptno from emp where emp.sal >= 800;

--8. 문제) 부서번호가 20번 이상인 사원의 모든 정보를 출력하라.
--select * from emp where emp.deptno >= 20;

--9. 문제) 이름이 K로 시작하는 사람보다 높은 이름을 가진 사람의 모든 
--         정보를 출력하라.
--select * from emp where emp.ename > 'K%';
		
--10. 문제) 입사일이 81/12/09 보다 먼저 입사한 사람들의 모든 정보를
  --        출력하라.
--select * from emp where emp.datetime < CONVERT(DATETIME, '1981-12-09');

--11. 문제) 입사번호가 7698보다 작거나 같은 사람들의 입사번호와 이름을
--          출력하라.
--select empno, ename from emp where emp.empno < 7698;

--12. 문제) 입사일이 81/04/02 보다 늦고 82/12/09 보다 빠른 사원의 이름,
--          월급, 부서번호를 출력하라.
--select ename, sal, empno from emp where emp.datetime > CONVERT(DATETIME, '1981-04-02') and emp.datetime < CONVERT(DATETIME, '1982-12-09');

--13. 문제) 급여가 $1,600보다 크고 $3,000보다 작은 사람의 이름, 직업, 
--          급여를 출력하라.
--select ename, job, sal from emp where emp.sal > 1600 and emp.sal < 3000;

--14. 문제) 사원번호가 7654와 7782 사이 이외의 사원의 모든 정보를
--          출력하라.
--select * from emp where not emp.empno > 7654 and emp.empno < 7782;

--15. 문제) 이름이 B와 J 사이의 모든 사원의 정보를 출력하라.
--select * from emp where emp.ename > '%B%' and emp.ename > '%J%';

--16. 문제) 입사일이 81년 이외에 입사한 사람의 모든 정보를 출력하라.
--select * from emp where not emp.datetime between CONVERT(DATETIME, '1981-01-01') and CONVERT(DATETIME, '1981-12-31');

--17. 문제) 직업이 MANAGER와 SALESMAN인 사람의 모든 정보를 출력하라.
--select * from emp where emp.job = 'MANAGER' or emp.job = 'SALESMAN';


--18. 문제) 부서번호와 20, 30번을 제외한 모든 사람의 이름, 사원번호, 
--select * from emp where not (emp.deptno = 20 or emp.deptno = 30)

--19. 문제) 이름이 S로 시작하는 사원의 사원번호, 이름, 입사일, 부서번호--
--          를 출력하라.
--select empno, ename, datetime, deptno from emp where emp.ename Like 'S%';

--20. 문제) 입사일이 81년도인 사람의 모든 정보를 출력하라
--select * from emp where emp.datetime between CONVERT(DATETIME, '1981-01-01') and CONVERT(DATETIME, '1981-12-31')


--21. 문제) 이름 중 S자가 들어가 있는 사람만 모든 정보를 출력하라.
--select * from emp where emp.ename Like '%S%';


--22. 문제) 이름이 S로 시작하고 마지막 글자가 T인 사람의 모든 정보를 
  --        출력하라(단, 이름은 전체 5자리이다)
--select * from emp where emp.ename Like 'S%' and emp.ename like '____T%';

--23. 문제) 첫 번째 문자는 관계없고, 두 번째 문자가 A인 사람의 정보를 
  --        출력하라.
--select * from emp where emp.ename Like '_A%';


--24. 문제) 커미션이 NULL인 사람의 정보를 출력하라.
--select * from emp where emp.comm is null;

--25. 문제) 커미션이 NULL이 아닌 사람의 모든 정보를 출력하라.
--select * from emp where emp.comm is not null;

--26. 문제) 부서가 30번 부서이고 급여가 $1,500 이상인 사람의 이름, 
--          부서 ,월급을 출력하라.
--select ename, deptno, sal from emp where emp.deptno = 30 and emp.sal >= 1500;

--27. 문제) 이름의 첫 글자가 K로 시작하거나 부서번호가 30인 사람의 
 --         사원번호, 이름, 부서번호를 출력하라.
--select empno, ename, deptno from emp where emp.ename Like 'K%' or emp.deptno = 30;

--28. 문제) 급여가 $1,500 이상이고 부서번호가 30번인 사원 중 직업이
   --       MANAGER인 사람의 정보를 출력하라
--select * from emp where emp.sal >= 1500 and emp.deptno = 30;

--29. 문제) 부서번호가 30인 사람 중 사원번호 SORT하라.
--select * from emp where emp.deptno = 30 Order by emp.empno

--30. 문제) 급여가 많은 순으로 SORT하라.
--select * from emp order by emp.sal DESC;

--31. 문제) 부서번호로 ASCENDING SORT한 후 급여가 많은 사람 순으로 
  --        출력하라.
 --select * from emp order by emp.deptno ASC, emp.sal DESC;

--32. 문제) 부서번호가 DESCENDING SORT하고, 이름 순으로 ASCENDING SORT,
  --        급여 순으로 DESCENDING SORT 하라.
--select * from emp order by emp.deptno DESC, emp.ename ASC, emp.sal DESC;

--PART2 -----------------------------------------------------------------------------------------------------------

--1. 문제) EMP Table에서 이름, 급여, 커미션 금액, 총액(sal + comm)을 
  --       구하여 총액이 많은 순서로 출력하라. 단, 커미션이 NULL인
    --     사람은 제외한다.
--select ename, sal, comm, (sal+comm) as 총액 from emp where emp.comm is not null order by (emp.sal + emp.comm) DESC; 


--2. 문제) 10번 부서의 모든 사람들이게 급여의 13%를 보너스로 지불하기로 
  --       하였다. 이름, 급여, 보너스 금액, 부서번호를 출력하라.
--select ename, sal, (sal*(13.0/100)) as 보너스 from emp where emp.deptno = 10;

--3. 문제) 30번 부서의 연봉을 계산하여 이름, 부서번호, 급여, 연봉을 
  --       출력하라. 단, 연말에 급여의 150%를 보너스로 지급한다.
--select ename, deptno, sal, ((sal * 12) + sal * 1.5) as 연봉 from emp where emp.deptno = 30;

--4. 문제 ) 부서번호가 20인 부서의 시간당 임금을 계산하여 출력하라. 
  --        단, 1달의 근무일수는 12일이고, 1일 근무시간은 5시간이다. 
    --      출력양식은 이름, 급여, 시간당 임금(소수이하 첫 번째 자리
      --    에서 반올림)을 출력하라
--select ename, sal, round((sal / 12.0 / 5.0),1) as 시급 from emp where emp.deptno = 20;


--5. 문제) 급여가 $1,500부터 $3,000 사이의 사람은 급여의 15%를 회비로 
  --       지불하기로 하였다. 이를 이름, 급여, 회비(소수점 두 자리에서
    --     반올림)를 출력하라.
--select ename, sal, (sal * 0.15) as 회비 from emp where emp.sal between 1500 and 3000 order by emp.sal DESC;
	
--6. 문제) 급여가 $2,000 이상인 모든 사람은 급여의 15%를 경조비로 내기
  --       로 하였다. 이름, 급여, 커미션(소수점 이하 절삭)를 출력하라.
--select ename, sal, floor(sal*0.15) as 경조사 from emp where emp.sal >= 2000;

--7. 문제) 입사일부터 지금까지의 날짜수를 출력하라. 부서번호, 이름, 입사
  --       일, 현재일, 근무일수(소수점 이하 절삭), 근무년수, 근무월수
    --     (30일 기준), 근무주수를 출력하라.
declare @date date = '2000-01-01';--GETDATE();
SELECT 
    deptno, 
    ename, 
    datetime AS 입사일,
    @date AS 현재일,
    DATEDIFF(DAY, datetime, @date) AS 근무일수,
    DATEDIFF(DAY, datetime, @date) / 365 AS 근무년수,
    DATEDIFF(DAY, datetime, @date) / 30 AS 근무월수,
    DATEDIFF(DAY, datetime, @date) / 7 AS 근무주수
FROM emp;
--8. 문제) 모든 사원의 실수령액을 계산하여 출력하라. 단, 급여가 많은 
  --       순으로 이름, 급여, 실수령액을 출력하라.(실수령액은 금여에 
    --     대해 10%의 세금을 뺀 금액)
select ename, sal, (sal - sal * 0.1) from emp order by emp.sal DESC;

--9. 문제) 입사일로부터 90일이 지난 후의 사원이름, 입사일, 90일 후의 
  --       날, 급여를 출력하라.
select ename, datetime, DATEADD(DAY, 90, datetime) as after_, sal from emp

--10. 문제) 입사일로부터 6개월이 지난 후의 입사일, 6개월 후의 날짜, 급여
  --        를 출력하라
select ename, datetime, DATEADD(MONTH, 6, datetime) as after_, sal from emp

--11. 문제) 입사한 달의 근무일수를 계산하여 부서번호, 이름, 근무일수를
  --        출력하라.
select ename, datetime, 30 - DAY(datetime) as workday from emp;

--12. 문제) 모든 사원의 60일이 지난 후의 ‘MONDAY’는 몇 년, 몇 월, 
  --        몇 일 인가를 구하여 이름, 입사일,’MONDAY’를 출력하라
select ename, datetime, DATENAME(WEEKDAY,(DATEADD(DAY, 60, datetime))) as after_ from emp
SELECT 
  ename,
  datetime AS 입사일,
  DATEADD(DAY, ( 60 + (9 - DATEPART(WEEKDAY, datetime)) % 7 ), datetime) AS _60일후_다음_월요일
FROM emp;

--13. 문제) 입사일로부터 오늘까지의 일수를 구하여 이름, 입사일, 근무일수
  --        를 출력하라.
select ename , datetime, DATEDIFF(DAY,datetime,CONVERT(DATETIME, '1990-01-01')) as 근무일수 from emp;

--14. 문제) 입사일을 ‘1996년 5월 14일’의 형태로 이름, 입사일을 출력
  --        하라.
select (CONVERt(char,YEAR(datetime))+'년'+convert(char, MONTH(datetime))+'월'+convert(char,DAY(datetime))+'일') as 입사일 from emp;

--15. 문제) 이름의 글자수가 6자 이상인 사람의 이름을 앞에서 3자만 구하
  --        여 소문자로 이름만을 출력하라.
select LEFT(ename, 3) from emp where LEN(emp.ename) >= 6;

--16. 문제) 10번 부서 월급의 평균, 최고, 최저, 인원수를 구하여 출력하라.
select AVG(sal), MAX(sal), MIN(sal), COUNT(sal) from emp where emp.deptno = 10;

--17. 문제) 각 부서별 급여의 평균, 최고, 최저, 인언수를 구하여 출력하라.
select deptno, AVG(sal), MAX(sal), MIN(sal), COUNT(sal) from emp Group by emp.deptno;

--18. 문제) 각 부서별 같은 업무를 하는 사람의 인원수를 구하여 부서번호,
  --        업무명, 인원수를 출력하라.
select deptno, job, (COUNT(*)) as people from emp group by emp.deptno, emp.job order by deptno

--19. 문제) 같은 업무를 하는 사람의 수가 4명 이상인 업무와 인원수를 
  --        출력하라
SELECT job, COUNT(*) as _count from emp group by job having COUNT(job) >= 4;

--20. 문제) 각 부서별 평균 월급, 전체 월급, 최고 월급, 최저 월급을 구하
  --        여 평균 월급이 많은 순으로 출력하라. 
select deptno, AVG(sal)as _avg, MAX(sal)as _max, MIN(sal) as _min, COUNT(sal)as _count from emp Group by emp.deptno order by AVG(sal) DESC;
--PART3-----------------------------------------------------------------------------------------------------------------

--1. 문제) EMP와 DEPT Table을 JOIN하여 부서번호, 부서명, 이름, 급여를 
  --       출력하라
select emp.deptno, dname, ename, sal from dept, emp where dept.deptno = emp.deptno;

--2. 문제) 이름이 ‘ALLEN’인 사원의 부서명을 출력하라.
select dname from dept, emp where dept.deptno = emp.deptno and emp.ename = 'ALLEN';

--3. 문제) DEPT Table에 있는 모든 부서를 출력하고, EMP Table에 있는 DATA
  --       와 JOIN하여 모든 사원의 이름, 부서번호, 부서명, 급여를 출력
    --     하라.
select ENAME , EMP.DEPTNO , DNAME , SAL from EMP , DEPT where EMP.DEPTNO = DEPT.DEPTNO;
	  

--4. 문제) EMP Table에 있는 EMPNO와 MGR을 이용하여 서로의 관계를 다음과
  --       같이 출력하라. ‘SMTH의 매니저는 FORD이다’
select e1.ENAME ,'의 매니저는',e2.ENAME,'이다' from EMP as e1,EMP as e2 where e1.MGR = e2.EMPNO;


--5. 문제) ‘ALLEN:의 직무와 같은 사람의 이름, 부서명, 급여, 직무를 
  --        출력하라.
select ename, dname, sal, dname from emp, dept where emp.deptno = dept.deptno and 
(job = (select job from emp where emp.ename = 'ALLEN'))


--6. 문제) ‘JONES’가 속해있는 부서의 모든 사람의 사원번호, 이름, 입사
  --       일, 급여를 출력하라
select empno, ename, datetime, sal from emp where emp.deptno = 
(select deptno from emp where emp.ename = 'JONES')

--7. 문제) 전체 사원의 평균 임금보다 많은 사원의 사원번호, 이름,
  --       부서명, 입사일, 지역, 급여를 출력하라.
select empno, ename, dname, datetime, loc, sal from dept, emp where dept.deptno = emp.deptno and
sal > (select AVG(sal) from emp)

--8. 문제) 10번 부서 사람들 중에서 20번 부서의 사원과 같은 업무를 하는
  --       사원의 사원번호, 이름, 부서명, 입사일, 지역을 출력하라.
select empno, ename, dname, datetime, loc from dept, emp where dept.deptno = emp.deptno and
dept.deptno = 10 and emp.job in (select job from emp where emp.deptno = 20)


--9. 문제) 10번 부서 중에서 30번 부서에는 없는 업무를 하는 사원의
  --       사원번호, 이름, 부서명, 입사일, 지역을 출력하라.
select emp.deptno, ename, dname, datetime, loc from dept, emp where dept.deptno = emp.deptno and
dept.deptno = 10 and not emp.job in (select job from emp where emp.deptno = 30)


--10. 문제) 10번 부서와 같은 일을 하는 사원의 사원번호, 이름, 부서명,
  --        지역, 급여를 급여가 많은 순으로 출력하라.
select emp.deptno, ename, dname, loc, sal from dept, emp where dept.deptno = emp.deptno and
emp.job in (select job from emp where emp.deptno = 10)order by emp.sal DESC

--11. 문제) ‘MARTIN’이나 ‘SCOTT의 급여와 같은 사원의 사원번호, 이름,
  --         급여를 출력하라.
select emp.deptno, ename, sal from emp where sal in 
(select sal from emp where emp.ename = 'MARTIN' or emp.ename = 'SCOTT')

--12. 문제) 급여가 30번 부서의 최고 급여보다 높은 사원의 사원번호, 
  --        이름, 급여를 출력하라.
select EMPNO , ENAME , SAL from EMP where SAL > (select MAX(SAL) from EMP where DEPTNO = 30)

--13. 문제) 급여가 30번 부서의 최저 급여보다 높은 사원의 사원번호, 
  --        이름, 급여를 출력하라.
select EMPNO , ENAME , SAL from EMP where SAL > (select MIN(SAL) from EMP where DEPTNO = 30)
