/* simple script to create the mysql database to be manipulated using the 
main.cpp program when executed */


create database attendancesys;

create table admin(
    adminname varchar(25),
    adminPass varchar(10)
);

create table student(
    studentName varchar(25),
    studentMatricule varchar(10),
    StudentAttendance varchar(10),
);