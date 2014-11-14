DELETE FROM `spell_script_names` WHERE `spell_id` = '34709';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(34709, 'spell_arena_shadow_sight');

UPDATE `gameobject_template` SET `faction`=0, `data1`=85 WHERE `entry`=184664;