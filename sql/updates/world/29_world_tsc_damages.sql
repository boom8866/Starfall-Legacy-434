-- Main Trash
UPDATE `creature_template` SET `dmg_multiplier`= 10 WHERE `entry` IN (42696, 43430, 43537, 43662, 42808, 42845, 42695, 42691, 42789);
UPDATE `creature_template` SET `mindmg`=465, `maxdmg`=697, `attackpower`=174, `dmg_multiplier`=37.7 WHERE `entry` IN (49667, 49660, 49662, 49669, 49663, 49655, 49666, 49665, 49664);

-- Crystalspawn Giant and Stonecore Bruiser
UPDATE `creature_template` SET `dmg_multiplier`= 10 WHERE `entry` IN (42810, 42692, 42428);
UPDATE `creature_template` SET `mindmg`=465, `maxdmg`=697, `attackpower`=174, `dmg_multiplier`=40.0 WHERE `entry` IN (49647, 49661, 49648);
