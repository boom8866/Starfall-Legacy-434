-- Generic Updates
UPDATE `creature_template` SET `InhabitType`= 4 WHERE `entry` IN (28332);

-- Forsaken Catapults (When Mechanist dies, the catapult becomes friendly and can be used as personal catapult)
DELETE FROM `vehicle_template_accessory` WHERE `entry`= 36283;
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(36283, 36292, 0, 1, 'Forsaken Catapult - Forsaken Mechanist', 8, 0);
