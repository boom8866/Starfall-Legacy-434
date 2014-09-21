UPDATE `creature_template` SET `minlevel`=17, `maxlevel`=17, `faction_A`=1771, `faction_H`=1771 WHERE `entry`=42697;
UPDATE `creature_template` SET `minlevel`=16, `maxlevel`=17, `faction_A`=1771, `faction_H`=1771 WHERE `entry`=42698;

DELETE FROM `creature_text` WHERE `entry`=42693;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(42693,0,0,'|cFF768EBDFive years ago, in the heart of the Deadmines...|r |TInterface\\QuestFrame\\UI-QUESTLOG-BOOKICON.BLP:32|t',41,0,100,0,0,0,'Comment');