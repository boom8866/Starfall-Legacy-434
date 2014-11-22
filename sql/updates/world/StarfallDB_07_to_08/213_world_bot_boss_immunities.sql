-- Halfus Immunities
UPDATE `creature_template` SET `mechanic_immune_mask`= 617299967, `flags_extra`= 1, `movementId`= 172 WHERE `entry` IN (44600, 46209, 46210, 46211);

-- Theralion and Valiona Immunities
UPDATE `creature_template` SET `mechanic_immune_mask`= 617299967, `flags_extra`= 1 WHERE `entry` IN (45992, 45993, 49897, 49898, 49899, 49903, 49904, 49905);
