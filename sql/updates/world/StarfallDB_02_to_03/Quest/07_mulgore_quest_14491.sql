UPDATE `creature_template` SET `ScriptName`='npc_agitated_earth_spirit' WHERE  `entry`=36845;
DELETE FROM `creature_text` WHERE `entry` = '36845';
INSERT INTO `creature_text` (`entry`, `text`, `type`, `probability`, `comment`) VALUES (36845, 'The spirit is displeased and attacks!', 41, 100, 'Agitated Earth Spirit Text Emote');
