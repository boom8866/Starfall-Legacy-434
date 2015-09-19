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

-- ---------------
12:40:16.205 -- morchok intro 1
12:40:26.689 -- lord afrasastrasz intro 1
12:40:36.330 -- tyrygosa image
12:40:39.231 -- image talk 1
12:40:50.182 -- image talk 2
12:40:56.953 -- lord intro 2
12:40:59.948 -- tyrygosa despawn
12:41:04.347 -- morchok intro 2

12:41:32.521 -- intro 3


*/

-- Resonating Crystal
UPDATE `creature_template` SET `minlevel`= 88, `maxlevel`= 88, `faction`= 14, `unit_flags`= 33587200, `unit_flags2`= 2048, `flags_extra`= 131, `scriptname`= 'npc_ds_resonating_crystal' WHERE `entry`= 55346;
REPLACE INTO `creature_template_addon` (`entry`, `auras`) VALUES
(55346, '109247'), -- Resonating Crystal
(55723, '108246'), -- Earthen Vortex
(57684, ''); -- Image of Tyrygosa

-- Earthen Vortex
UPDATE `creature_template` SET `minlevel`= 88, `maxlevel`= 88, `faction`= 6, `VehicleId`= 1896, `unit_flags`= 2312, `unit_flags2`= 67584, `speed_run`= 2.0, `scriptname`= 'npc_ds_earthen_vortex' WHERE `entry`= 55723;

-- Loes Afrasastrasz
UPDATE `creature_template` SET `scriptname`= 'npc_ds_lord_afrasastrasz' WHERE `entry`= 55476;

-- Image of Tyrygosa
UPDATE `creature_template` SET `minlevel`= 87, `maxlevel`= 87, `faction`= 35, `unit_flags`= 32768, `unit_flags2`= 33556480, `exp`= 3, `scriptname`= 'npc_ds_image_of_tyrygosa' WHERE `entry`= 57684;

-- Ancient Water Lord
SET @ENTRY := 57160;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
UPDATE `creature_template` SET `AIName`="", `scriptname`= 'npc_ds_ancient_water_lord' WHERE `entry`=@ENTRY;

-- Earthen Destroyer
SET @ENTRY := 57158;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
UPDATE `creature_template` SET `AIName`="", `scriptname`= 'npc_ds_earthen_destroyer' WHERE `entry`=@ENTRY;

DELETE FROM `creature_text` WHERE entry IN (55265, 55476, 57684);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
-- Morchok
(55265, 0, 0, 'No mortal shall turn me from my task.', 14, 0, 100, 0, 0, 26282, 'Morchok - Intro 1'),
(55265, 1, 0, 'Cowards. Weaklings. Come down and fight, or I will bring you down.', 14, 0, 100, 0, 0, 26270, 'Morchok - Intro 2'),
(55265, 2, 0, 'You cannot hide in this temple forever, Shaman.', 14, 0, 100, 0, 0, 26271, 'Morchok - Intro 3'),
(55265, 3, 0, 'I will turn this tower to rubble, and scatter it across the wastes.', 14, 0, 100, 0, 0, 26272, 'Morchok - Intro 4'),
(55265, 4, 0, 'You seek to halt an avalanche. I will bury you.', 14, 0, 100, 0, 0, 26268, 'Morchok - Aggro'),
(55265, 5, 0, 'I am unstoppable.', 14, 0, 100, 0, 0, 26285, 'Morchok - Slay 1'),
(55265, 5, 1, 'It was inevitable.', 14, 0, 100, 0, 0, 26286, 'Morchok - Slay 2'),
(55265, 5, 2, 'Ground to dust.', 14, 0, 100, 0, 0, 26287, 'Morchok - Slay 3'),
(55265, 6, 0, 'Flee, and die.', 14, 0, 100, 0, 0, 26283, 'Morchok - Resonating Crystal 1'),
(55265, 6, 1, 'Run, and perish.', 14, 0, 100, 0, 0, 26284, 'Morchok - Resonating Crystal 2'),
(55265, 7, 0, '%s summons a Resonating Crystal!', 41, 0, 100, 0, 0, 26284, 'Morchok - Announce Resonating Crystal'),
(55265, 8, 0, 'The stone calls...', 14, 0, 100, 0, 0, 26274, 'Morchok - Earthen  Vortex 1'),
(55265, 8, 1, 'The ground shakes...', 14, 0, 100, 0, 0, 26275, 'Morchok - Earthen Vortex 2'),
(55265, 8, 2, 'The rocks tremble...', 14, 0, 100, 0, 0, 26276, 'Morchok - Earthen Vortex 3'),
(55265, 8, 3, 'The surface quakes...', 14, 0, 100, 0, 0, 26277, 'Morchok - Earthen Vortex 4'),
(55265, 9, 0, '...and the black blood of the earth consumes you.', 14, 0, 100, 0, 0, 26278, 'Morchok - Blood of the Earth 1'),
(55265, 9, 1, '...and there is no escape from the Old Gods.', 14, 0, 100, 0, 0, 26279, 'Morchok - Blood of the Earth 2'),
(55265, 9, 2, '...and the rage of the true gods follows.', 14, 0, 100, 0, 0, 26280, 'Morchok - Blood of the Earth 3'),
(55265, 9, 3, '...and you drown in the hate of The Master.', 14, 0, 100, 0, 0, 26281, 'Morchok - Blood of the Earth 4'),
(55265, 10, 0, 'Impossible. This cannot be. The tower... must... fall...', 14, 0, 100, 0, 0, 26269, 'Morchok - Death'),
-- Lord Afrasastrasz
(55476, 0, 0, 'Wyrmrest Accord, Attack!', 14, 0, 100, 0, 0, 26531, 'Lord Afrasastrasz - Intro 1'),
(55476, 1, 0, 'Tyrygosa yet lives! We must press on, to the Temple!', 14, 0, 100, 0, 0, 26532, 'Lord Afrasastrasz - Intro 2'),
-- Image of Tyrygosa
(57684, 0, 0, 'They have broken our defenses... the very earth turns against us in Deathwing''s name.', 14, 0, 100, 0, 0, 26305, 'Image of Tyrygosa - Intro 1'),
(57684, 1, 0, 'You must hurry... Wyrmrest falls as we speak... all... is lost...', 14, 0, 100, 0, 0, 26306, 'Image of Tyrygosa - Intro 2');


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
