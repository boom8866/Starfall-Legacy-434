/*
12:42:21.459 -- engage
12:42:27.574 -- crush armor #1
12:42:35.858 -- crush armor #2

12:42:39.602 -- resonating crystal #1
12:42:54.156 -- resonating crystal #2

12:42:40.491 -- resonating crystal summon

12:43:08.041 -- knockback self vertical
12:43:08.072 -- exlosion

12:42:34.017 -- stomp #1
12:42:45.670 -- stomp #2

12:43:17.135 -- earthen vortex cast
12:43:17.135 -- falling fragments

12:43:21.878

12:43:25.325 -- play spell visual 21700
12:43:24.233 -- black blood of the earth


*/

-- Resonating Crystal
UPDATE `creature_template` SET `minlevel`= 88, `maxlevel`= 88, `faction`= 14, `unit_flags`= 33587200, `unit_flags2`= 2048, `flags_extra`= 131, `scriptname`= 'npc_ds_resonating_crystal' WHERE `entry`= 55346;
REPLACE INTO `creature_template_addon` (`entry`, `auras`) VALUES
(55346, '109247'), -- Resonating Crystal
(55723, '108246'); -- Earthen Vortex

-- Earthen Vortex
UPDATE `creature_template` SET `minlevel`= 88, `maxlevel`= 88, `faction`= 6, `VehicleId`= 1896, `unit_flags`= 2312, `unit_flags2`= 67584, `speed_run`= 2.0, `scriptname`= 'npc_ds_earthen_vortex' WHERE `entry`= 55723;

REPLACE INTO `spell_script_names` (`spell_id`, `scriptname`) VALUES
(104573 ,'spell_ds_target_selection'),
(103528 ,'spell_ds_target_selection'),
(103545 ,'spell_ds_resonating_crystal_explosion'),
(108572 ,'spell_ds_resonating_crystal_explosion'),
(110041 ,'spell_ds_resonating_crystal_explosion'),
(110040 ,'spell_ds_resonating_crystal_explosion'),
(103414, 'spell_ds_stomp'),
(108571, 'spell_ds_stomp'),
(109033, 'spell_ds_stomp'),
(109034, 'spell_ds_stomp'),
(103176, 'spell_ds_falling_fragments');
