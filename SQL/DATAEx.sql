--PART1 -------------------------------------------------------------------------------------------------------------------

--1. ����) �μ���ȣ�� 10���� �μ��� ��� �� �����ȣ, �̸�, ������ ����϶�
--select empno, ename, sal from emp where emp.deptno = 10;

--2. ����) �����ȣ�� 7369�� ��� �� �̸�, �Ի���, �μ���ȣ�� ����϶�.
--select ename, datetime, deptno from emp where emp.empno = 7369;

--3. ����) �̸��� ALLEN�� ����� ��� ������ ����϶�.
--select * from emp where emp.ename = 'ALLEN';

--4. ����) �Ի����� 83/01/12�� ����� �̸�, �μ���ȣ, ������ ����϶�.
--select ename, deptno, sal from emp where emp.datetime = CONVERT(DATETIME, '1981-06-09');

--5. ����) ������ MANAGER�� �ƴ� ����� ��� ������ ����϶�.
--select * from emp where not emp.job = 'MANAGER';

--6. ����) �Ի����� 81/04/02 ���Ŀ� �Ի��� ����� ������ ����϶�.
--select * from emp where emp.datetime > CONVERT(DATETIME, '1981-04-02');

--7. ����) �޿��� $800 �̻��� ����� �̸�, �޿�, �μ���ȣ�� ����϶�.
--select ename, sal, deptno from emp where emp.sal >= 800;

--8. ����) �μ���ȣ�� 20�� �̻��� ����� ��� ������ ����϶�.
--select * from emp where emp.deptno >= 20;

--9. ����) �̸��� K�� �����ϴ� ������� ���� �̸��� ���� ����� ��� 
--         ������ ����϶�.
--select * from emp where emp.ename > 'K%';
		
--10. ����) �Ի����� 81/12/09 ���� ���� �Ի��� ������� ��� ������
  --        ����϶�.
--select * from emp where emp.datetime < CONVERT(DATETIME, '1981-12-09');

--11. ����) �Ի��ȣ�� 7698���� �۰ų� ���� ������� �Ի��ȣ�� �̸���
--          ����϶�.
--select empno, ename from emp where emp.empno < 7698;

--12. ����) �Ի����� 81/04/02 ���� �ʰ� 82/12/09 ���� ���� ����� �̸�,
--          ����, �μ���ȣ�� ����϶�.
--select ename, sal, empno from emp where emp.datetime > CONVERT(DATETIME, '1981-04-02') and emp.datetime < CONVERT(DATETIME, '1982-12-09');

--13. ����) �޿��� $1,600���� ũ�� $3,000���� ���� ����� �̸�, ����, 
--          �޿��� ����϶�.
--select ename, job, sal from emp where emp.sal > 1600 and emp.sal < 3000;

--14. ����) �����ȣ�� 7654�� 7782 ���� �̿��� ����� ��� ������
--          ����϶�.
--select * from emp where not emp.empno > 7654 and emp.empno < 7782;

--15. ����) �̸��� B�� J ������ ��� ����� ������ ����϶�.
--select * from emp where emp.ename > '%B%' and emp.ename > '%J%';

--16. ����) �Ի����� 81�� �̿ܿ� �Ի��� ����� ��� ������ ����϶�.
--select * from emp where not emp.datetime between CONVERT(DATETIME, '1981-01-01') and CONVERT(DATETIME, '1981-12-31');

--17. ����) ������ MANAGER�� SALESMAN�� ����� ��� ������ ����϶�.
--select * from emp where emp.job = 'MANAGER' or emp.job = 'SALESMAN';


--18. ����) �μ���ȣ�� 20, 30���� ������ ��� ����� �̸�, �����ȣ, 
--select * from emp where not (emp.deptno = 20 or emp.deptno = 30)

--19. ����) �̸��� S�� �����ϴ� ����� �����ȣ, �̸�, �Ի���, �μ���ȣ--
--          �� ����϶�.
--select empno, ename, datetime, deptno from emp where emp.ename Like 'S%';

--20. ����) �Ի����� 81�⵵�� ����� ��� ������ ����϶�
--select * from emp where emp.datetime between CONVERT(DATETIME, '1981-01-01') and CONVERT(DATETIME, '1981-12-31')


--21. ����) �̸� �� S�ڰ� �� �ִ� ����� ��� ������ ����϶�.
--select * from emp where emp.ename Like '%S%';


--22. ����) �̸��� S�� �����ϰ� ������ ���ڰ� T�� ����� ��� ������ 
  --        ����϶�(��, �̸��� ��ü 5�ڸ��̴�)
--select * from emp where emp.ename Like 'S%' and emp.ename like '____T%';

--23. ����) ù ��° ���ڴ� �������, �� ��° ���ڰ� A�� ����� ������ 
  --        ����϶�.
--select * from emp where emp.ename Like '_A%';


--24. ����) Ŀ�̼��� NULL�� ����� ������ ����϶�.
--select * from emp where emp.comm is null;

--25. ����) Ŀ�̼��� NULL�� �ƴ� ����� ��� ������ ����϶�.
--select * from emp where emp.comm is not null;

--26. ����) �μ��� 30�� �μ��̰� �޿��� $1,500 �̻��� ����� �̸�, 
--          �μ� ,������ ����϶�.
--select ename, deptno, sal from emp where emp.deptno = 30 and emp.sal >= 1500;

--27. ����) �̸��� ù ���ڰ� K�� �����ϰų� �μ���ȣ�� 30�� ����� 
 --         �����ȣ, �̸�, �μ���ȣ�� ����϶�.
--select empno, ename, deptno from emp where emp.ename Like 'K%' or emp.deptno = 30;

--28. ����) �޿��� $1,500 �̻��̰� �μ���ȣ�� 30���� ��� �� ������
   --       MANAGER�� ����� ������ ����϶�
--select * from emp where emp.sal >= 1500 and emp.deptno = 30;

--29. ����) �μ���ȣ�� 30�� ��� �� �����ȣ SORT�϶�.
--select * from emp where emp.deptno = 30 Order by emp.empno

--30. ����) �޿��� ���� ������ SORT�϶�.
--select * from emp order by emp.sal DESC;

--31. ����) �μ���ȣ�� ASCENDING SORT�� �� �޿��� ���� ��� ������ 
  --        ����϶�.
 --select * from emp order by emp.deptno ASC, emp.sal DESC;

--32. ����) �μ���ȣ�� DESCENDING SORT�ϰ�, �̸� ������ ASCENDING SORT,
  --        �޿� ������ DESCENDING SORT �϶�.
--select * from emp order by emp.deptno DESC, emp.ename ASC, emp.sal DESC;

--PART2 -----------------------------------------------------------------------------------------------------------

--1. ����) EMP Table���� �̸�, �޿�, Ŀ�̼� �ݾ�, �Ѿ�(sal + comm)�� 
  --       ���Ͽ� �Ѿ��� ���� ������ ����϶�. ��, Ŀ�̼��� NULL��
    --     ����� �����Ѵ�.
--select ename, sal, comm, (sal+comm) as �Ѿ� from emp where emp.comm is not null order by (emp.sal + emp.comm) DESC; 


--2. ����) 10�� �μ��� ��� ������̰� �޿��� 13%�� ���ʽ��� �����ϱ�� 
  --       �Ͽ���. �̸�, �޿�, ���ʽ� �ݾ�, �μ���ȣ�� ����϶�.
--select ename, sal, (sal*(13.0/100)) as ���ʽ� from emp where emp.deptno = 10;

--3. ����) 30�� �μ��� ������ ����Ͽ� �̸�, �μ���ȣ, �޿�, ������ 
  --       ����϶�. ��, ������ �޿��� 150%�� ���ʽ��� �����Ѵ�.
--select ename, deptno, sal, ((sal * 12) + sal * 1.5) as ���� from emp where emp.deptno = 30;

--4. ���� ) �μ���ȣ�� 20�� �μ��� �ð��� �ӱ��� ����Ͽ� ����϶�. 
  --        ��, 1���� �ٹ��ϼ��� 12���̰�, 1�� �ٹ��ð��� 5�ð��̴�. 
    --      ��¾���� �̸�, �޿�, �ð��� �ӱ�(�Ҽ����� ù ��° �ڸ�
      --    ���� �ݿø�)�� ����϶�
--select ename, sal, round((sal / 12.0 / 5.0),1) as �ñ� from emp where emp.deptno = 20;


--5. ����) �޿��� $1,500���� $3,000 ������ ����� �޿��� 15%�� ȸ��� 
  --       �����ϱ�� �Ͽ���. �̸� �̸�, �޿�, ȸ��(�Ҽ��� �� �ڸ�����
    --     �ݿø�)�� ����϶�.
--select ename, sal, (sal * 0.15) as ȸ�� from emp where emp.sal between 1500 and 3000 order by emp.sal DESC;
	
--6. ����) �޿��� $2,000 �̻��� ��� ����� �޿��� 15%�� ������� ����
  --       �� �Ͽ���. �̸�, �޿�, Ŀ�̼�(�Ҽ��� ���� ����)�� ����϶�.
--select ename, sal, floor(sal*0.15) as ������ from emp where emp.sal >= 2000;

--7. ����) �Ի��Ϻ��� ���ݱ����� ��¥���� ����϶�. �μ���ȣ, �̸�, �Ի�
  --       ��, ������, �ٹ��ϼ�(�Ҽ��� ���� ����), �ٹ����, �ٹ�����
    --     (30�� ����), �ٹ��ּ��� ����϶�.
declare @date date = '2000-01-01';--GETDATE();
SELECT 
    deptno, 
    ename, 
    datetime AS �Ի���,
    @date AS ������,
    DATEDIFF(DAY, datetime, @date) AS �ٹ��ϼ�,
    DATEDIFF(DAY, datetime, @date) / 365 AS �ٹ����,
    DATEDIFF(DAY, datetime, @date) / 30 AS �ٹ�����,
    DATEDIFF(DAY, datetime, @date) / 7 AS �ٹ��ּ�
FROM emp;
--8. ����) ��� ����� �Ǽ��ɾ��� ����Ͽ� ����϶�. ��, �޿��� ���� 
  --       ������ �̸�, �޿�, �Ǽ��ɾ��� ����϶�.(�Ǽ��ɾ��� �ݿ��� 
    --     ���� 10%�� ������ �� �ݾ�)
select ename, sal, (sal - sal * 0.1) from emp order by emp.sal DESC;

--9. ����) �Ի��Ϸκ��� 90���� ���� ���� ����̸�, �Ի���, 90�� ���� 
  --       ��, �޿��� ����϶�.
select ename, datetime, DATEADD(DAY, 90, datetime) as after_, sal from emp

--10. ����) �Ի��Ϸκ��� 6������ ���� ���� �Ի���, 6���� ���� ��¥, �޿�
  --        �� ����϶�
select ename, datetime, DATEADD(MONTH, 6, datetime) as after_, sal from emp

--11. ����) �Ի��� ���� �ٹ��ϼ��� ����Ͽ� �μ���ȣ, �̸�, �ٹ��ϼ���
  --        ����϶�.
select ename, datetime, 30 - DAY(datetime) as workday from emp;

--12. ����) ��� ����� 60���� ���� ���� ��MONDAY���� �� ��, �� ��, 
  --        �� �� �ΰ��� ���Ͽ� �̸�, �Ի���,��MONDAY���� ����϶�
select ename, datetime, DATENAME(WEEKDAY,(DATEADD(DAY, 60, datetime))) as after_ from emp
SELECT 
  ename,
  datetime AS �Ի���,
  DATEADD(DAY, ( 60 + (9 - DATEPART(WEEKDAY, datetime)) % 7 ), datetime) AS _60����_����_������
FROM emp;

--13. ����) �Ի��Ϸκ��� ���ñ����� �ϼ��� ���Ͽ� �̸�, �Ի���, �ٹ��ϼ�
  --        �� ����϶�.
select ename , datetime, DATEDIFF(DAY,datetime,CONVERT(DATETIME, '1990-01-01')) as �ٹ��ϼ� from emp;

--14. ����) �Ի����� ��1996�� 5�� 14�ϡ��� ���·� �̸�, �Ի����� ���
  --        �϶�.
select (CONVERt(char,YEAR(datetime))+'��'+convert(char, MONTH(datetime))+'��'+convert(char,DAY(datetime))+'��') as �Ի��� from emp;

--15. ����) �̸��� ���ڼ��� 6�� �̻��� ����� �̸��� �տ��� 3�ڸ� ����
  --        �� �ҹ��ڷ� �̸����� ����϶�.
select LEFT(ename, 3) from emp where LEN(emp.ename) >= 6;

--16. ����) 10�� �μ� ������ ���, �ְ�, ����, �ο����� ���Ͽ� ����϶�.
select AVG(sal), MAX(sal), MIN(sal), COUNT(sal) from emp where emp.deptno = 10;

--17. ����) �� �μ��� �޿��� ���, �ְ�, ����, �ξ���� ���Ͽ� ����϶�.
select deptno, AVG(sal), MAX(sal), MIN(sal), COUNT(sal) from emp Group by emp.deptno;

--18. ����) �� �μ��� ���� ������ �ϴ� ����� �ο����� ���Ͽ� �μ���ȣ,
  --        ������, �ο����� ����϶�.
select deptno, job, (COUNT(*)) as people from emp group by emp.deptno, emp.job order by deptno

--19. ����) ���� ������ �ϴ� ����� ���� 4�� �̻��� ������ �ο����� 
  --        ����϶�
SELECT job, COUNT(*) as _count from emp group by job having COUNT(job) >= 4;

--20. ����) �� �μ��� ��� ����, ��ü ����, �ְ� ����, ���� ������ ����
  --        �� ��� ������ ���� ������ ����϶�. 
select deptno, AVG(sal)as _avg, MAX(sal)as _max, MIN(sal) as _min, COUNT(sal)as _count from emp Group by emp.deptno order by AVG(sal) DESC;
--PART3-----------------------------------------------------------------------------------------------------------------

--1. ����) EMP�� DEPT Table�� JOIN�Ͽ� �μ���ȣ, �μ���, �̸�, �޿��� 
  --       ����϶�
select emp.deptno, dname, ename, sal from dept, emp where dept.deptno = emp.deptno;

--2. ����) �̸��� ��ALLEN���� ����� �μ����� ����϶�.
select dname from dept, emp where dept.deptno = emp.deptno and emp.ename = 'ALLEN';

--3. ����) DEPT Table�� �ִ� ��� �μ��� ����ϰ�, EMP Table�� �ִ� DATA
  --       �� JOIN�Ͽ� ��� ����� �̸�, �μ���ȣ, �μ���, �޿��� ���
    --     �϶�.
select ENAME , EMP.DEPTNO , DNAME , SAL from EMP , DEPT where EMP.DEPTNO = DEPT.DEPTNO;
	  

--4. ����) EMP Table�� �ִ� EMPNO�� MGR�� �̿��Ͽ� ������ ���踦 ������
  --       ���� ����϶�. ��SMTH�� �Ŵ����� FORD�̴١�
select e1.ENAME ,'�� �Ŵ�����',e2.ENAME,'�̴�' from EMP as e1,EMP as e2 where e1.MGR = e2.EMPNO;


--5. ����) ��ALLEN:�� ������ ���� ����� �̸�, �μ���, �޿�, ������ 
  --        ����϶�.
select ename, dname, sal, dname from emp, dept where emp.deptno = dept.deptno and 
(job = (select job from emp where emp.ename = 'ALLEN'))


--6. ����) ��JONES���� �����ִ� �μ��� ��� ����� �����ȣ, �̸�, �Ի�
  --       ��, �޿��� ����϶�
select empno, ename, datetime, sal from emp where emp.deptno = 
(select deptno from emp where emp.ename = 'JONES')

--7. ����) ��ü ����� ��� �ӱݺ��� ���� ����� �����ȣ, �̸�,
  --       �μ���, �Ի���, ����, �޿��� ����϶�.
select empno, ename, dname, datetime, loc, sal from dept, emp where dept.deptno = emp.deptno and
sal > (select AVG(sal) from emp)

--8. ����) 10�� �μ� ����� �߿��� 20�� �μ��� ����� ���� ������ �ϴ�
  --       ����� �����ȣ, �̸�, �μ���, �Ի���, ������ ����϶�.
select empno, ename, dname, datetime, loc from dept, emp where dept.deptno = emp.deptno and
dept.deptno = 10 and emp.job in (select job from emp where emp.deptno = 20)


--9. ����) 10�� �μ� �߿��� 30�� �μ����� ���� ������ �ϴ� �����
  --       �����ȣ, �̸�, �μ���, �Ի���, ������ ����϶�.
select emp.deptno, ename, dname, datetime, loc from dept, emp where dept.deptno = emp.deptno and
dept.deptno = 10 and not emp.job in (select job from emp where emp.deptno = 30)


--10. ����) 10�� �μ��� ���� ���� �ϴ� ����� �����ȣ, �̸�, �μ���,
  --        ����, �޿��� �޿��� ���� ������ ����϶�.
select emp.deptno, ename, dname, loc, sal from dept, emp where dept.deptno = emp.deptno and
emp.job in (select job from emp where emp.deptno = 10)order by emp.sal DESC

--11. ����) ��MARTIN���̳� ��SCOTT�� �޿��� ���� ����� �����ȣ, �̸�,
  --         �޿��� ����϶�.
select emp.deptno, ename, sal from emp where sal in 
(select sal from emp where emp.ename = 'MARTIN' or emp.ename = 'SCOTT')

--12. ����) �޿��� 30�� �μ��� �ְ� �޿����� ���� ����� �����ȣ, 
  --        �̸�, �޿��� ����϶�.
select EMPNO , ENAME , SAL from EMP where SAL > (select MAX(SAL) from EMP where DEPTNO = 30)

--13. ����) �޿��� 30�� �μ��� ���� �޿����� ���� ����� �����ȣ, 
  --        �̸�, �޿��� ����϶�.
select EMPNO , ENAME , SAL from EMP where SAL > (select MIN(SAL) from EMP where DEPTNO = 30)
