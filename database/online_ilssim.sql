-- MySQL dump 10.14  Distrib 5.5.44-MariaDB, for Linux (x86_64)
--
-- Host: localhost    Database: online_ilssim
-- ------------------------------------------------------
-- Server version	5.5.44-MariaDB
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO,ANSI' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table "AktivierteLeitstellen"
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE "AktivierteLeitstellen" (
  "idAktivierteLeitstellen" int(11) NOT NULL,
  PRIMARY KEY ("idAktivierteLeitstellen")
);
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table "AktivierteLeitstellen"
--

INSERT INTO "AktivierteLeitstellen" VALUES (1);

--
-- Table structure for table "Einsatz"
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE "Einsatz" (
  "idEinsatz" int(11) NOT NULL,
  "PosLat" decimal(10,7) NOT NULL,
  "PosLong" decimal(10,7) NOT NULL,
  "Ort" varchar(100) NOT NULL,
  "Strasse" varchar(100) NOT NULL,
  "StrassenNr" int(11) NOT NULL,
  "AnrufZeit" timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  "EndZeit" datetime DEFAULT NULL,
  "idObjekt" int(11) NOT NULL,
  "idEinsatzTyp" int(11) NOT NULL,
  "idLeitstelle" int(11) NOT NULL,
  PRIMARY KEY ("idEinsatz")
);
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table "Einsatz"
--

INSERT INTO "Einsatz" VALUES (1,48.3027950,14.3005860,'Linz','Gruberstraﬂe',92,'2014-04-12 16:21:12',NULL,1,1,1);

--
-- Table structure for table "Einsatz_has_Patient"
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE "Einsatz_has_Patient" (
  "Einsatz_idEinsatz" int(11) NOT NULL,
  "Patient_idPatient" int(11) NOT NULL,
  PRIMARY KEY ("Einsatz_idEinsatz","Patient_idPatient"),
  KEY "fk_Einsatz_has_Patient_Patient1" ("Patient_idPatient"),
  KEY "fk_Einsatz_has_Patient_Einsatz1" ("Einsatz_idEinsatz"),
  CONSTRAINT "fk_Einsatz_has_Patient_Einsatz1" FOREIGN KEY ("Einsatz_idEinsatz") REFERENCES "Einsatz" ("idEinsatz") ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT "fk_Einsatz_has_Patient_Patient1" FOREIGN KEY ("Patient_idPatient") REFERENCES "Patient" ("idPatient") ON DELETE NO ACTION ON UPDATE NO ACTION
);
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table "Einsatz_has_Patient"
--


--
-- Table structure for table "FahrzeugPosition"
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE "FahrzeugPosition" (
  "idFahrzeug" int(11) NOT NULL,
  "AktuelleZeit" timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  "PosLat" decimal(10,7) NOT NULL,
  "PosLong" decimal(10,7) NOT NULL,
  PRIMARY KEY ("idFahrzeug","AktuelleZeit")
);
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table "FahrzeugPosition"
--

INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 20:44:05',48.3045930,14.2987750);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 20:44:06',48.3045930,14.2987750);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 20:44:07',48.3045830,14.2986270);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 20:44:08',48.3037810,14.2988060);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 20:44:11',48.3035490,14.2988580);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 20:44:13',48.3030990,14.2989590);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 20:44:16',48.3029940,14.2990120);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 20:44:17',48.3030230,14.2991010);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 20:44:18',48.3030870,14.2992960);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 20:44:19',48.3033170,14.2999870);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 20:44:21',48.3033950,14.3002210);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 20:44:23',48.3034480,14.3003810);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 20:44:24',48.3033470,14.3004000);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 20:44:25',48.3031030,14.3004620);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 20:44:26',48.3028420,14.3005270);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 20:44:27',48.3028200,14.3005340);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 20:44:28',48.3027930,14.3005410);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 20:44:29',48.3027930,14.3005410);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 20:45:28',48.3027930,14.3005410);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 20:45:29',48.3027930,14.3005410);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 20:45:30',48.3028200,14.3005340);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 20:45:31',48.3027930,14.3005410);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 20:45:32',48.3027930,14.3005410);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 20:46:08',48.3045930,14.2987750);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 20:46:09',48.3045930,14.2987750);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 20:46:10',48.3047670,14.2985860);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 20:46:11',48.3045830,14.2986270);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 20:46:12',48.3045830,14.2986270);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:22:30',48.3045930,14.2987750);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:22:31',48.3045930,14.2987750);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:22:32',48.3045830,14.2986270);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:22:33',48.3037810,14.2988060);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:22:36',48.3035490,14.2988580);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:22:38',48.3030990,14.2989590);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:22:41',48.3029940,14.2990120);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:22:42',48.3030230,14.2991010);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:22:43',48.3030870,14.2992960);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:22:44',48.3033170,14.2999870);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:22:46',48.3033950,14.3002210);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:22:48',48.3034480,14.3003810);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:22:49',48.3033470,14.3004000);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:22:50',48.3031030,14.3004620);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:22:51',48.3028420,14.3005270);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:22:52',48.3028200,14.3005340);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:22:53',48.3027930,14.3005410);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:22:54',48.3027930,14.3005410);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:29:04',48.3045930,14.2987750);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:29:05',48.3045930,14.2987750);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:29:06',48.3045830,14.2986270);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:29:07',48.3037810,14.2988060);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:29:11',48.3035490,14.2988580);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:29:12',48.3030990,14.2989590);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:29:15',48.3029940,14.2990120);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:29:16',48.3030230,14.2991010);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:29:17',48.3030870,14.2992960);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:29:18',48.3033170,14.2999870);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:29:21',48.3033950,14.3002210);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:29:22',48.3034480,14.3003810);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:29:23',48.3033470,14.3004000);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:29:24',48.3031030,14.3004620);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:29:25',48.3028420,14.3005270);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:34:28',48.3045930,14.2987750);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:34:29',48.3045930,14.2987750);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:34:30',48.3045830,14.2986270);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:34:31',48.3037810,14.2988060);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:34:34',48.3035490,14.2988580);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:34:35',48.3030990,14.2989590);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:34:38',48.3029940,14.2990120);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:34:39',48.3030230,14.2991010);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:34:40',48.3030870,14.2992960);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:34:41',48.3033170,14.2999870);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:34:44',48.3033950,14.3002210);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:34:45',48.3034480,14.3003810);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:34:46',48.3033470,14.3004000);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:34:47',48.3031030,14.3004620);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:43:21',48.3045930,14.2987750);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:43:22',48.3045930,14.2987750);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:53:44',48.3045930,14.2987750);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:53:45',48.3037810,14.2988060);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:53:50',48.3029940,14.2990120);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:53:55',48.3033950,14.3002210);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:54:01',48.3028200,14.3005340);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:54:06',48.3028200,14.3005340);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:55:06',48.3028200,14.3005340);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-09 21:55:07',48.3028200,14.3005340);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-15 21:31:04',48.3045930,14.2987750);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-15 21:31:05',48.3045930,14.2987750);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-15 21:31:06',48.3045830,14.2986270);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-15 21:31:07',48.3037810,14.2988060);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-15 21:31:10',48.3035490,14.2988580);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-15 21:31:13',48.3030990,14.2989590);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-15 21:31:15',48.3029940,14.2990120);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-15 21:31:16',48.3030230,14.2991010);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-15 21:31:17',48.3030870,14.2992960);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-15 21:31:18',48.3033170,14.2999870);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-15 21:31:20',48.3033950,14.3002210);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-15 21:31:21',48.3034480,14.3003810);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-15 21:31:24',48.3033470,14.3004000);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-15 21:31:25',48.3031030,14.3004620);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-15 21:31:26',48.3028420,14.3005270);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-15 21:31:27',48.3028200,14.3005340);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-15 21:31:28',48.3027930,14.3005410);
INSERT INTO "FahrzeugPosition" VALUES (2940,'2015-10-15 21:31:29',48.3027930,14.3005410);

--
-- Table structure for table "FahrzeugStatus"
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE "FahrzeugStatus" (
  "idFahrzeugStatus" int(11) NOT NULL,
  "Name" varchar(45) NOT NULL,
  "SystemStatus" tinyint(1) NOT NULL,
  PRIMARY KEY ("idFahrzeugStatus")
);
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table "FahrzeugStatus"
--

INSERT INTO "FahrzeugStatus" VALUES (1,'Nicht Einsatzbereit',0);
INSERT INTO "FahrzeugStatus" VALUES (2,'Einsatzbereit',0);
INSERT INTO "FahrzeugStatus" VALUES (3,'Einsatz Akzeptiert',0);
INSERT INTO "FahrzeugStatus" VALUES (4,'Ankunft Einsatzort',0);
INSERT INTO "FahrzeugStatus" VALUES (5,'Abfahrt Einsatzort',0);
INSERT INTO "FahrzeugStatus" VALUES (6,'Ankunft Zielort',0);
INSERT INTO "FahrzeugStatus" VALUES (7,'Abfahrt Zielort',0);
INSERT INTO "FahrzeugStatus" VALUES (8,'Eintreffen Dienststelle',0);
INSERT INTO "FahrzeugStatus" VALUES (9,'Fahrzeug Besetzen',1);
INSERT INTO "FahrzeugStatus" VALUES (10,'Patient Gefunden',1);

--
-- Table structure for table "FahrzeugUpdate"
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE "FahrzeugUpdate" (
  "idFahrzeug" int(11) NOT NULL,
  "AktuelleZeit" timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  "FahrzeugStatus_idFahrzeugStatus" int(11) NOT NULL,
  "ZielPosLat" decimal(10,7) NOT NULL,
  "ZielPosLong" decimal(10,7) NOT NULL,
  "Einsatz_idEinsatz" int(11) DEFAULT NULL,
  "Patient_idPatient" int(11) DEFAULT NULL,
  "Einsatz_Blau" tinyint(1) DEFAULT NULL,
  "IsServerStatus" tinyint(1) NOT NULL DEFAULT '0',
  "UsersOnline_idUsersOnline" int(11) DEFAULT NULL,
  PRIMARY KEY ("idFahrzeug","AktuelleZeit"),
  KEY "fk_FahrzeugStatus_Einsatz" ("Einsatz_idEinsatz"),
  KEY "fk_FahrzeugStatus_Patient1" ("Patient_idPatient"),
  KEY "fk_FahrzeugStatus_FahrzeugStatus1_idx" ("FahrzeugStatus_idFahrzeugStatus"),
  KEY "fk_FahrzeugUpdate_UsersOnline1_idx" ("UsersOnline_idUsersOnline"),
  CONSTRAINT "fk_FahrzeugStatus_Einsatz" FOREIGN KEY ("Einsatz_idEinsatz") REFERENCES "Einsatz" ("idEinsatz") ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT "fk_FahrzeugStatus_FahrzeugStatus1" FOREIGN KEY ("FahrzeugStatus_idFahrzeugStatus") REFERENCES "FahrzeugStatus" ("idFahrzeugStatus") ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT "fk_FahrzeugStatus_Patient1" FOREIGN KEY ("Patient_idPatient") REFERENCES "Patient" ("idPatient") ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT "fk_FahrzeugUpdate_UsersOnline1" FOREIGN KEY ("UsersOnline_idUsersOnline") REFERENCES "UsersOnline" ("idUsersOnline") ON DELETE NO ACTION ON UPDATE NO ACTION
);
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table "FahrzeugUpdate"
--

INSERT INTO "FahrzeugUpdate" VALUES (2940,'2015-10-09 20:43:45',3,48.3027950,14.3005860,1,NULL,1,1,NULL);
INSERT INTO "FahrzeugUpdate" VALUES (2940,'2015-10-09 20:44:28',4,48.3027950,14.3005860,1,NULL,1,1,NULL);
INSERT INTO "FahrzeugUpdate" VALUES (2940,'2015-10-09 20:44:48',10,48.3027950,14.3005860,1,NULL,1,1,NULL);
INSERT INTO "FahrzeugUpdate" VALUES (2940,'2015-10-09 20:45:08',5,48.3027950,14.3005860,1,NULL,1,1,NULL);
INSERT INTO "FahrzeugUpdate" VALUES (2940,'2015-10-09 20:45:28',6,48.3027950,14.3005860,1,NULL,1,1,NULL);
INSERT INTO "FahrzeugUpdate" VALUES (2940,'2015-10-09 20:45:48',7,48.3027950,14.3005860,1,NULL,1,1,NULL);
INSERT INTO "FahrzeugUpdate" VALUES (2940,'2015-10-09 20:46:11',2,48.3027950,14.3005860,NULL,NULL,1,1,NULL);
INSERT INTO "FahrzeugUpdate" VALUES (2940,'2015-10-09 21:22:10',3,48.3027950,14.3005860,1,NULL,1,1,NULL);
INSERT INTO "FahrzeugUpdate" VALUES (2940,'2015-10-09 21:22:53',4,48.3027950,14.3005860,1,NULL,1,1,NULL);
INSERT INTO "FahrzeugUpdate" VALUES (2940,'2015-10-09 21:23:13',10,48.3027950,14.3005860,1,NULL,1,1,NULL);
INSERT INTO "FahrzeugUpdate" VALUES (2940,'2015-10-09 21:23:38',5,48.3027950,14.3005860,1,NULL,1,1,NULL);
INSERT INTO "FahrzeugUpdate" VALUES (2940,'2015-10-09 21:28:44',3,48.3027950,14.3005860,1,NULL,1,1,NULL);
INSERT INTO "FahrzeugUpdate" VALUES (2940,'2015-10-09 21:34:08',3,48.3027950,14.3005860,1,NULL,1,1,NULL);
INSERT INTO "FahrzeugUpdate" VALUES (2940,'2015-10-09 21:40:58',3,48.3027950,14.3005860,1,NULL,1,1,NULL);
INSERT INTO "FahrzeugUpdate" VALUES (2940,'2015-10-09 21:43:01',3,48.3027950,14.3005860,1,NULL,1,1,NULL);
INSERT INTO "FahrzeugUpdate" VALUES (2940,'2015-10-09 21:43:21',4,48.3027950,14.3005860,1,NULL,1,1,NULL);
INSERT INTO "FahrzeugUpdate" VALUES (2940,'2015-10-09 21:46:28',3,48.3027950,14.3005860,1,NULL,1,1,NULL);
INSERT INTO "FahrzeugUpdate" VALUES (2940,'2015-10-09 21:50:59',3,48.3027950,14.3005860,1,NULL,1,1,NULL);
INSERT INTO "FahrzeugUpdate" VALUES (2940,'2015-10-09 21:53:24',3,48.3027950,14.3005860,1,NULL,1,1,NULL);
INSERT INTO "FahrzeugUpdate" VALUES (2940,'2015-10-09 21:54:06',4,48.3027950,14.3005860,1,NULL,1,1,NULL);
INSERT INTO "FahrzeugUpdate" VALUES (2940,'2015-10-09 21:54:26',10,48.3027950,14.3005860,1,NULL,1,1,NULL);
INSERT INTO "FahrzeugUpdate" VALUES (2940,'2015-10-09 21:54:46',5,48.3027950,14.3005860,1,NULL,1,1,NULL);
INSERT INTO "FahrzeugUpdate" VALUES (2940,'2015-10-09 21:55:06',6,48.3027950,14.3005860,1,NULL,1,1,NULL);
INSERT INTO "FahrzeugUpdate" VALUES (2940,'2015-10-15 21:30:44',3,48.3027950,14.3005860,1,NULL,1,1,NULL);
INSERT INTO "FahrzeugUpdate" VALUES (2940,'2015-10-15 21:31:27',4,48.3027950,14.3005860,1,NULL,1,1,NULL);

--
-- Table structure for table "Flughafen"
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE "Flughafen" (
  "idFlughafen" varchar(4) NOT NULL,
  "Name" varchar(100) NOT NULL,
  PRIMARY KEY ("idFlughafen")
);
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table "Flughafen"
--


--
-- Table structure for table "METAR"
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE "METAR" (
  "idFlughafen" varchar(4) NOT NULL,
  "Time" timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  "Gewitter" tinyint(1) NOT NULL DEFAULT '0',
  "Regen" tinyint(1) NOT NULL DEFAULT '0',
  "Schnee" tinyint(1) NOT NULL DEFAULT '0',
  "Eis" tinyint(1) NOT NULL DEFAULT '0',
  "Hagel" tinyint(1) NOT NULL DEFAULT '0',
  "Nebel" tinyint(1) NOT NULL DEFAULT '0',
  "Temperatur" tinyint(4) NOT NULL DEFAULT '0',
  PRIMARY KEY ("idFlughafen","Time"),
  CONSTRAINT "fk_METAR_Flughafen1" FOREIGN KEY ("idFlughafen") REFERENCES "Flughafen" ("idFlughafen") ON DELETE NO ACTION ON UPDATE NO ACTION
);
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table "METAR"
--


--
-- Table structure for table "Patient"
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE "Patient" (
  "idPatient" int(11) NOT NULL,
  "idVorname" int(11) NOT NULL,
  "idNachname" int(11) NOT NULL,
  "Versicherungsnummer" int(11) NOT NULL,
  "Geburtstag" date NOT NULL,
  "idWohnobjekt" int(11) NOT NULL,
  "TelNummer" int(11) NOT NULL,
  "Tot" tinyint(1) NOT NULL DEFAULT '0',
  "PatientenStandort_idPatientenStandort" int(11) NOT NULL,
  PRIMARY KEY ("idPatient"),
  KEY "fk_Patient_PatientenStandort1_idx" ("PatientenStandort_idPatientenStandort"),
  CONSTRAINT "fk_Patient_PatientenStandort1" FOREIGN KEY ("PatientenStandort_idPatientenStandort") REFERENCES "PatientenStandort" ("idPatientenStandort") ON DELETE NO ACTION ON UPDATE NO ACTION
);
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table "Patient"
--


--
-- Table structure for table "PatientenStandort"
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE "PatientenStandort" (
  "idPatientenStandort" int(11) NOT NULL,
  "Name" varchar(45) NOT NULL,
  PRIMARY KEY ("idPatientenStandort")
);
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table "PatientenStandort"
--

INSERT INTO "PatientenStandort" VALUES (1,'Zuhause');
INSERT INTO "PatientenStandort" VALUES (2,'Krankenhaus');
INSERT INTO "PatientenStandort" VALUES (3,'Einsatz');

--
-- Table structure for table "UsersOnline"
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE "UsersOnline" (
  "idUsersOnline" int(11) NOT NULL,
  "idUser" int(11) NOT NULL,
  "idLeitstelle" int(11) NOT NULL,
  "StartTime" timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  "EndTime" datetime DEFAULT NULL,
  PRIMARY KEY ("idUsersOnline")
);
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table "UsersOnline"
--

/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2015-10-31 19:16:54
