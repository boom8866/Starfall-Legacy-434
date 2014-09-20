UPDATE `gameobject_template` SET `scriptname`= 'go_crate_of_mandrake_essence' WHERE `entry`= 196394;

UPDATE `creature_template` SET `scriptname`= 'npc_forsaken_assassin' WHERE `entry`= 36207;
UPDATE `creature_template` SET `scriptname`= 'npc_slain_watchman', `unit_flags`= 2 | 512 WHERE `entry`= 36205;
REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(36207, 0, 0, 'Gilneas will soon belong to the Forsaken!', 12, 0, 100, 0, 0, 0, 'Forsaken Assassin - Attack');
