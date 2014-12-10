UPDATE `creature_template` SET `scriptname`= 'npc_hoo_sun_touched_servant', `AIName`= '' WHERE  `entry` IN (39366, 39369, 39370);

-- Sun-Touched Sprite
UPDATE `creature_template` SET `difficulty_entry_1`= 49283 WHERE `entry`= 39369;
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction`= 91, `exp`= 3, `AIName`= '' WHERE `entry` IN (39369, 49283);

-- Sun-Touched-Spriteling
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction`= 91, `exp`= 3 WHERE `entry`= 39370;

-- Sun-Touched Speaker
UPDATE `creature_template` SET `scriptname`= 'npc_hoo_sun_touched_speaker', `AIName`= '' WHERE `entry`= 39373;
UPDATE `creature_template` SET `unit_flags`= 0, `unit_flags2`= 2048, `faction`= 91 WHERE `entry` IN (39373, 49285);

REPLACE INTO `spell_script_names` (`spell_id`, `scriptname`) VALUES
(74632, 'spell_hoo_flame_ring_script');

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (39366, 39369, 39370, 49283, 39373, 49285, 49282);
