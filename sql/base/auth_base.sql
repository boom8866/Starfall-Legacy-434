/*
SQLyog Community v10.0 
MySQL - 5.5.19-log : Database - auth
*********************************************************************
*/

/*!40101 SET NAMES utf8 */;

/*!40101 SET SQL_MODE=''*/;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;
CREATE DATABASE /*!32312 IF NOT EXISTS*/`auth` /*!40100 DEFAULT CHARACTER SET latin1 */;

/*Table structure for table `account` */

DROP TABLE IF EXISTS `account`;

CREATE TABLE `account` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT COMMENT 'Identifier',
  `username` varchar(32) NOT NULL DEFAULT '',
  `sha_pass_hash` varchar(40) NOT NULL DEFAULT '',
  `sessionkey` longtext,
  `v` longtext,
  `s` longtext,
  `email` text,
  `joindate` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `last_ip` varchar(30) NOT NULL DEFAULT '127.0.0.1',
  `failed_logins` int(11) unsigned NOT NULL DEFAULT '0',
  `locked` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `last_login` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `online` tinyint(4) NOT NULL DEFAULT '0',
  `expansion` tinyint(3) unsigned NOT NULL DEFAULT '3',
  `mutetime` bigint(40) unsigned NOT NULL DEFAULT '0',
  `mutereason` varchar(255) NOT NULL DEFAULT '',
  `muteby` varchar(50) NOT NULL DEFAULT '',
  `locale` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `os` varchar(4) NOT NULL DEFAULT '',
  `recruiter` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `idx_username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Account System';

/*Data for the table `account` */

insert  into `account`(`id`,`username`,`sha_pass_hash`,`sessionkey`,`v`,`s`,`email`,`joindate`,`last_ip`,`failed_logins`,`locked`,`last_login`,`online`,`expansion`,`mutetime`,`mutereason`,`muteby`,`locale`,`os`,`recruiter`) values (1,'ADMIN','8301316D0D8448A34FA6D0C6BF1CBFA2B4A1A93A','B90609FC05738F91500991DEE86ECC7F32FC74D80AF2D573A43400C4472C22244DDF035D53B00A51','2736C45005C6025E9AA78B9C7E683E4C8C11DFA1068BD89C3678F34AB1889A74','F705A5678955BF531EC1A9A44066B60ECAA5A6FDF6F6B1774D97DB02B6EB3CE1',NULL,'2013-05-06 23:10:57','127.0.0.1',0,0,'2013-05-29 21:06:53',0,3,0,'','',3,'Win',0);

/*Table structure for table `account_access` */

DROP TABLE IF EXISTS `account_access`;

CREATE TABLE `account_access` (
  `id` int(11) unsigned NOT NULL,
  `gmlevel` tinyint(3) unsigned NOT NULL,
  `RealmID` int(11) NOT NULL DEFAULT '-1',
  PRIMARY KEY (`id`,`RealmID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

/*Data for the table `account_access` */

insert  into `account_access`(`id`,`gmlevel`,`RealmID`) values (1,5,-1);

/*Table structure for table `account_banned` */

DROP TABLE IF EXISTS `account_banned`;

CREATE TABLE `account_banned` (
  `id` int(11) NOT NULL DEFAULT '0' COMMENT 'Account id',
  `bandate` int(10) unsigned NOT NULL DEFAULT '0',
  `unbandate` int(10) unsigned NOT NULL DEFAULT '0',
  `bannedby` varchar(50) NOT NULL,
  `banreason` varchar(255) NOT NULL,
  `active` tinyint(4) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`,`bandate`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Ban List';

/*Data for the table `account_banned` */

/*Table structure for table `bug_tickets` */

DROP TABLE IF EXISTS `bug_tickets`;

CREATE TABLE `bug_tickets` (
  `ticketId` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `realm` int(10) unsigned NOT NULL DEFAULT '0',
  `guid` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'Global Unique Identifier of ticket creator',
  `message` text NOT NULL,
  `createTime` int(10) unsigned NOT NULL DEFAULT '0',
  `pool` varchar(32) NOT NULL,
  `mapId` smallint(5) unsigned NOT NULL DEFAULT '0',
  `posX` float NOT NULL DEFAULT '0',
  `posY` float NOT NULL DEFAULT '0',
  `posZ` float NOT NULL DEFAULT '0',
  `closedBy` int(10) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ticketId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Support System';

/*Data for the table `bug_tickets` */

/*Table structure for table `ip_banned` */

DROP TABLE IF EXISTS `ip_banned`;

CREATE TABLE `ip_banned` (
  `ip` varchar(15) NOT NULL DEFAULT '127.0.0.1',
  `bandate` int(10) unsigned NOT NULL,
  `unbandate` int(10) unsigned NOT NULL,
  `bannedby` varchar(50) NOT NULL DEFAULT '[Console]',
  `banreason` varchar(255) NOT NULL DEFAULT 'no reason',
  PRIMARY KEY (`ip`,`bandate`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Banned IPs';

/*Data for the table `ip_banned` */

/*Table structure for table `logs` */

DROP TABLE IF EXISTS `logs`;

CREATE TABLE `logs` (
  `time` int(14) NOT NULL,
  `realm` int(4) NOT NULL,
  `type` int(4) NOT NULL,
  `level` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `level2` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `string` text
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

/*Data for the table `logs` */

/*Table structure for table `realmcharacters` */

DROP TABLE IF EXISTS `realmcharacters`;

CREATE TABLE `realmcharacters` (
  `realmid` int(11) unsigned NOT NULL DEFAULT '0',
  `acctid` bigint(20) unsigned NOT NULL,
  `numchars` tinyint(3) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`realmid`,`acctid`),
  KEY `acctid` (`acctid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Realm Character Tracker';

/*Data for the table `realmcharacters` */

insert  into `realmcharacters`(`realmid`,`acctid`,`numchars`) values (1,1,4);

/*Table structure for table `realmlist` */

DROP TABLE IF EXISTS `realmlist`;

CREATE TABLE `realmlist` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(32) NOT NULL DEFAULT '',
  `address` varchar(255) NOT NULL DEFAULT '127.0.0.1',
  `localAddress` varchar(255) NOT NULL DEFAULT '127.0.0.1',
  `localSubnetMask` varchar(255) NOT NULL DEFAULT '255.255.255.0',
  `port` int(11) NOT NULL DEFAULT '8085',
  `icon` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `flag` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `timezone` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `allowedSecurityLevel` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `population` float unsigned NOT NULL DEFAULT '0',
  `online` int(11) NOT NULL DEFAULT '0',
  `gamebuild` int(11) unsigned NOT NULL DEFAULT '13623',
  `color` tinyint(3) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `idx_name` (`name`)
) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Realm System';

/*Data for the table `realmlist` */

insert  into `realmlist`(`id`,`name`,`address`,`localAddress`,`localSubnetMask`,`port`,`icon`,`flag`,`timezone`,`allowedSecurityLevel`,`population`,`online`,`gamebuild`,`color`) values (1,'Cataclysm 4.3.4','127.0.0.1','127.0.0.1','255.255.255.0',8085,0,1,1,0,0,0,15595,1);

/*Table structure for table `uptime` */

DROP TABLE IF EXISTS `uptime`;

CREATE TABLE `uptime` (
  `realmid` int(11) unsigned NOT NULL,
  `starttime` bigint(20) unsigned NOT NULL DEFAULT '0',
  `startstring` varchar(64) NOT NULL DEFAULT '',
  `uptime` bigint(20) unsigned NOT NULL DEFAULT '0',
  `maxplayers` smallint(5) unsigned NOT NULL DEFAULT '0',
  `revision` varchar(255) NOT NULL DEFAULT 'Trinitycore',
  PRIMARY KEY (`realmid`,`starttime`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Uptime system';

/*Data for the table `uptime` */

insert  into `uptime`(`realmid`,`starttime`,`startstring`,`uptime`,`maxplayers`,`revision`) values (1,1367874611,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, Debug)'),(1,1367876120,'',1837,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, Debug)'),(1,1367941139,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1367941670,'',612,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1367942827,'',4285,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1367947839,'',612,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1367948778,'',1225,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1367950420,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1367951064,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1367951495,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1367951885,'',612,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1367953061,'',610,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1367960827,'',1837,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1367962962,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368031698,'',2448,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368034601,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368052721,'',2441,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368056757,'',611,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368059465,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368060129,'',6119,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368066652,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368113316,'',612,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368114319,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368114565,'',3673,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368118301,'',9796,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368128492,'',1225,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368129831,'',7932,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368138237,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368206736,'',613,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368207925,'',4283,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368212724,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368212912,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368213569,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368213984,'',2447,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368216653,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368216703,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368217193,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368217272,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368217364,'',16514,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368234330,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368234573,'',6735,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368364329,'',4285,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368368810,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368369074,'',613,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368369864,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368370198,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368370352,'',1225,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368371872,'',3673,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368375688,'',2448,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368378612,'',1837,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368380733,'',1837,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368383232,'',1224,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368385368,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368385627,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368385890,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368385939,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368386322,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368386509,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368386829,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368387188,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368388106,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368388601,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368389210,'',613,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368390476,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368548670,'',4285,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368553204,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368560274,'',4897,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368565567,'',1225,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368629428,'',1836,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368631681,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368632156,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368632389,'',3673,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368636399,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368636999,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368637501,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368637771,'',1830,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368639964,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368892883,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368893537,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368894279,'',1224,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368896362,'',22004,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368918585,'',611,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368919588,'',12222,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368963856,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1368964450,'',2443,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1369675897,'',1835,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1369684594,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1369684917,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1369685602,'',1224,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1369687242,'',1241,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1369854308,'',1263,1,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)'),(1,1369857400,'',0,0,'StrawberryCore rev. unknown 1970-01-01 00:00:00 +0000 (Archived branch) (Win64, RelWithDebInfo)');

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;
