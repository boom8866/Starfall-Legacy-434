UPDATE `creature_template_addon` SET `emote`=431 WHERE  `entry`=41671;
DELETE FROM `spell_script_names` WHERE `spell_id` = '77819';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(77819, 'spell_rune_of_return');

DELETE FROM `creature_text` WHERE `entry`=41671;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(41671,0,0,'You\'re the best thing I\'ve seen since the troggs showed up!.',12,0,100,0,0,0,'Comment'),
(41671,0,1,'I thought I would die down here.',12,0,100,0,0,0,'Comment'),
(41671,0,2,'I thought they were going to tear me apart!.',12,0,100,0,0,0,'Comment'),
(41671,0,3,'I can\'t wait to get home to my family. Thank you, stranger.',12,0,100,0,0,0,'Comment');