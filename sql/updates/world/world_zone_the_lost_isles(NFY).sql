UPDATE `creature_template` SET `ScriptName`='npc_geargrinder_gizmo_intro' WHERE `entry`=36600;
UPDATE `creature_template` SET `ScriptName`='npc_doc_zapnozzle_intro' WHERE `entry`=36608;

DELETE FROM `creature_text` WHERE `entry`=36608;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(36608,0,0,'Gizmo, what are you doing just sittin there? Don\'t you recognize who that is laying next to you?!',12,0,100,1,0,0,'Comment'),
(36608,1,0,'That\'s $n, $G, the whole reason we\'re still breathing and not crispy fried critters back on Kezan.',12,0,100,1,0,0,'Comment'),
(36608,2,0,'Stay back, I\'m going to resuscitate him! I hope these wet jumper cables don\'t kill us all!',12,0,100,1,0,0,'Comment'),
(36608,3,0,'Come on! Clear!',12,0,100,1,0,0,'Comment'),
(36608,4,0,'Thats all I\'ve got. It\'s up to $g, now. You hear me, $n? Come on, snap out of it! Don\'t go into the Light!',12,0,100,1,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=36600;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(36600,0,0,'That\'s $n?! Sorry, Doc. I thought he was dead!',12,0,100,1,0,0,'Comment');

UPDATE `creature_template` SET `InhabitType`=7 WHERE `entry`=36608;

DELETE FROM `creature_questrelation` WHERE `id` = '36608' AND `quest` = '14239';
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES
(36608, 14239);

DELETE FROM `creature_involvedrelation` WHERE `id` = '36608' AND `quest` = '14239';
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
(36608, 14239);

UPDATE `quest_template` SET `PrevQuestId`='14239' WHERE `Id`=14474;