# Void Seeker, 41371 49304

UPDATE `creature_template` SET `AIName`= 'SmartAI', `ScriptName`= '' WHERE `entry`= 41371;
UPDATE `creature_template` SET `mechanic_immune_mask`= 667893759 WHERE `entry`= 49304;
DELETE FROM `smart_scripts` WHERE (`entryorguid`=41371 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(41371, 0, 0, 0, 0, 0, 100, 6, 3000, 6000, 30000, 32000, 11, 76903, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'cast - Anti-Magic Prison on victim'),
(41371, 0, 1, 0, 0, 0, 100, 6, 4000, 6000, 4000, 6000, 11, 76146, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'cast - Shadow Bolt Volley on self (aoe)');

# Void Lord, 41364 49303

UPDATE `creature_template` SET `mechanic_immune_mask`= 667893759, `AIName`= 'SmartAI' WHERE `entry`= 41364;
UPDATE `creature_template` SET `mechanic_immune_mask`= 667893759 WHERE `entry`= 49303;
DELETE FROM `smart_scripts` WHERE (`entryorguid`=41364 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(41364, 0, 0, 1, 1, 0, 100, 7, 0, 0, 0, 0, 22, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'set - phase 1'),
(41364, 0, 1, 2, 61, 0, 100, 7, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'set - attack off'),
(41364, 0, 2, 0, 61, 0, 100, 7, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'set - movment off'),
(41364, 0, 5, 6, 0, 0, 100, 7, 0, 0, 0, 0, 12, 39266, 8, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'sum - void rift on self'),
(41364, 0, 6, 0, 61, 0, 100, 7, 0, 0, 0, 0, 11, 77470, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'cast - void infusion on self'),
(41364, 0, 10, 0, 0, 0, 100, 7, 30000, 30000, 0, 0, 22, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'set - phase 2 after 30sec combat'),
(41364, 0, 11, 12, 0, 2, 100, 7, 0, 0, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'set - attack on'),
(41364, 0, 12, 13, 61, 2, 100, 7, 0, 0, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'set - movment on'),
(41364, 0, 13, 14, 61, 2, 100, 7, 0, 0, 0, 0, 75, 77466, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'cast - grow on self'),
(41364, 0, 14, 15, 61, 2, 100, 7, 0, 0, 0, 0, 75, 77466, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'cast - grow on self'),
(41364, 0, 15, 16, 61, 2, 100, 7, 0, 0, 0, 0, 75, 77466, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'cast - grow on self'),
(41364, 0, 16, 0, 61, 2, 100, 7, 0, 0, 0, 0, 75, 77466, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'cast - grow on self'),
(41364, 0, 20, 0, 0, 3, 100, 6, 2000, 4000, 30000, 34000, 12, 39266, 8, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'cast - sum on random target'),
(41364, 0, 21, 0, 0, 2, 100, 6, 3000, 6000, 4000, 6000, 11, 76146, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'cast - Shadow Bolt Volley on self (aoe)'),
(41364, 0, 22, 0, 0, 2, 100, 6, 6000, 8000, 12000, 14000, 11, 77475, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'cast - void burst on self (aoe)'),
(41364, 0, 30, 0, 7, 0, 100, 7, 0, 0, 0, 0, 28, 77466, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'remove - grow on evade');

UPDATE `creature_template` SET `AIName`= 'SmartAI', `flags_extra`= 128, `faction`= 16, `unit_flags`= 33554818 WHERE `entry`= 39266;
DELETE FROM `smart_scripts` WHERE (`entryorguid`=39266 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(39266, 0, 0, 1, 54, 0, 100, 7, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'set - movement off'),
(39266, 0, 1, 2, 61, 0, 100, 7, 0, 0, 0, 0, 75, 73699, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'cast - aura void rift on self - on spawn'),
(39266, 0, 2, 0, 61, 0, 100, 7, 0, 0, 0, 0, 41, 30000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'despawn - after 30sec');
