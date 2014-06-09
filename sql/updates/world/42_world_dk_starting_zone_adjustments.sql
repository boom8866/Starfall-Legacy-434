UPDATE `quest_template` SET `PrevQuestId`='12738' WHERE `Id`=28649;

DELETE FROM `conditions` WHERE `SourceEntry` = '12742' AND `SourceTypeOrReferenceId` = '20';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 16, 12742, 1, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '12742' AND `SourceTypeOrReferenceId` = '19';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 16, 12742, 1, 0);

DELETE FROM `creature` WHERE `guid` IN (835954, 835953);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(835954, 49356, 609, 1, 4, 0, 0, 1331.51, -5760.02, 137.646, 3.22117, 300, 0, 0, 0, 0, 0, 0, 0, 0),
(835953, 49355, 609, 1, 4, 0, 0, 1320.46, -5757.53, 137.565, 6.25752, 300, 0, 0, 0, 0, 0, 0, 0, 0);

UPDATE `creature_template` SET `minlevel`=53, `maxlevel`=53, `faction_A`=7, `faction_H`=7, `ScriptName`='npc_a_special_surprise' WHERE `entry` IN (49355,49356);

DELETE FROM `creature_addon` WHERE `guid` IN (835954, 835953);
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(835954, 0, 0, 65544, 1, 0, 'NULL'),
(835953, 0, 0, 65544, 1, 0, 'NULL');

DELETE FROM `creature_text` WHERE `entry`=49355;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(49355,0,0,'Come to finish the job, have you? ',12,0,100,0,0,0,'Comment'),
(49355,3,0,'You\'ll look me in the eyes when... ',12,0,100,0,0,0,'Comment'),
(49355,10,0,'$n? ',12,0,100,0,0,0,'Comment'),
(49355,13,0,'$n, I\'d recognize that face anywhere... What... What have they done to you, $n? ',12,0,100,0,0,0,'Comment'),
(49355,57,0,'You don\'t remember me? We were both servants of Arugal back in Silverpine Forest. We put up with his merciless torture for ages. It was you who saved me on that fateful night when we escaped Shadowfang Keep. ',12,0,100,0,0,0,'Comment'),
(49355,59,0,'Without you I would have died. YOU! The most noble worgen I ever knew. ',12,0,100,0,0,0,'Comment'),
(49355,37,0,'What have they done to you, $n? How could this have happened? ',12,0,100,0,0,0,'Comment'),
(49355,43,0,'Remember the worgen you once were! You were our savior! Fight this! ',12,0,100,0,0,0,'Comment'),
(49355,52,0,'Listen to me, $n. You must fight against the Lich King\'s control. He is a monster that wants to see this world - our world - in ruin. Don\'t let him use you to accomplish his goals. You were once a hero and you can be again. Fight, damn you! Fight his control! ',12,0,100,0,0,0,'Comment'),
(49355,53,0,'Do it, $n! Put me out of my misery! ',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=49355;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(49355,0,0,'Come to finish the job, have you? ',12,0,100,0,0,0,'Comment'),
(49355,3,0,'You\'ll look me in the eyes when... ',12,0,100,0,0,0,'Comment'),
(49355,10,0,'$n? ',12,0,100,0,0,0,'Comment'),
(49355,13,0,'$n, I\'d recognize that face anywhere... What... What have they done to you, $n? ',12,0,100,0,0,0,'Comment'),
(49355,57,0,'You don\'t remember me? We were both servants of Arugal back in Silverpine Forest. We put up with his merciless torture for ages. It was you who saved me on that fateful night when we escaped Shadowfang Keep. ',12,0,100,0,0,0,'Comment'),
(49355,59,0,'Without you I would have died. YOU! The most noble worgen I ever knew. ',12,0,100,0,0,0,'Comment'),
(49355,37,0,'What have they done to you, $n? How could this have happened? ',12,0,100,0,0,0,'Comment'),
(49355,43,0,'Remember the worgen you once were! You were our savior! Fight this! ',12,0,100,0,0,0,'Comment'),
(49355,52,0,'Listen to me, $n. You must fight against the Lich King\'s control. He is a monster that wants to see this world - our world - in ruin. Don\'t let him use you to accomplish his goals. You were once a hero and you can be again. Fight, damn you! Fight his control! ',12,0,100,0,0,0,'Comment'),
(49355,53,0,'Do it, $n! Put me out of my misery! ',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=49356;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(49356,54,0,'C... can\'t we work this out somehow?',12,0,100,0,0,0,'Comment'),
(49356,55,0,'Alright, j... just let me... let me st... stand up. ',12,0,100,0,0,0,'Comment'),
(49356,10,0,'$n? ',12,0,100,0,0,0,'Comment'),
(49356,13,0,'$n, I\'d recognize that face anywhere... What... What have they done to you, $n? You don\'t remember me, $n? I lost count of the number of jobs you and I ran back in the day on Kezan. Then I picked up a real bad Kaja\'Cola habit and you saved me! It was you who took me to Kalimdor to join the Steamwheedle Cartel. You were the only good goblin I knew. That\'s how I ended up in the Argent Dawn, because I knew it\'s what you woulda done. How could this have happened to you? ',12,0,100,0,0,0,'Comment'),
(49356,57,0,'You don\'t remember me? We were both servants of Arugal back in Silverpine Forest. We put up with his merciless torture for ages. It was you who saved me on that fateful night when we escaped Shadowfang Keep. ',12,0,100,0,0,0,'Comment'),
(49356,58,0,'Remember the goblin you once were! You were my best friend! Fight this!',12,0,100,0,0,0,'Comment'),
(49356,60,0,'What have they done to you, $n? How could this have happened? ',12,0,100,0,0,0,'Comment'),
(49356,43,0,'Listen to me, $n. You must fight against the Lich King\'s control. He is a monster who wants to see this world - our world - in ruin. Don\'t let him use you to accomplish his goals. You were once a hero and can be again. Fight, damn you! Fight his control!',12,0,100,0,0,0,'Comment'),
(49356,52,0,'There... There\'s no more time for me. I\'m done for. Finish me off, $n. ',12,0,100,0,0,0,'Comment'),
(49356,53,0,'Do it, $n! Put me out of my misery! ',12,0,100,0,0,0,'Comment');

UPDATE `quest_template` SET `PrevQuestId`='12738' WHERE `Id`=28650;