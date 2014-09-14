-- Generic Updates
UPDATE `creature_template` SET `InhabitType`= 4 WHERE `entry` IN (28332);

-- Forsaken Catapults (When Mechanist dies, the catapult becomes friendly and can be used as personal catapult)
DELETE FROM `vehicle_template_accessory` WHERE `entry`= 36283;
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(36283, 36292, 0, 1, 'Forsaken Catapult - Forsaken Mechanist', 8, 0);

-- Quest 14348 You can't take 'em aline
-- Note: Liam must be visible to make the credit working properly
UPDATE `creature_template` SET `scriptname`= 'npc_horrid_abomination' WHERE `entry`= 36231;
REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(36231, 0, 0, 'GAH!!!!  I CAN''T SEE IN HERE!!!!', 12, 0, 100, 0, 0, 20908, 'Horrid Abomination - Keg Placed'),
(36231, 0, 1, 'Barrel smell like gunpowder...', 12, 0, 100, 0, 0, 20909, 'Horrid Abomination - Keg Placed'),
(36231, 0, 2, 'This not be good...', 12, 0, 100, 0, 0, 20910, 'Horrid Abomination - Keg Placed'),
(36231, 0, 3, 'Uh-oh... this gonna hurts me...', 12, 0, 100, 0, 0, 20911, 'Horrid Abomination - Keg Placed'),
(36231, 0, 4, 'I gots bad feeling...', 12, 0, 100, 0, 0, 20912, 'Horrid Abomination - Keg Placed'),
(36231, 0, 5, 'Get back here!  I smashes you!', 12, 0, 100, 0, 0, 20913, 'Horrid Abomination - Keg Placed');
