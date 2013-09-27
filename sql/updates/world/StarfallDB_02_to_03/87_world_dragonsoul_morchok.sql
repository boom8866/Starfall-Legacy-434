
UPDATE `creature_template` SET `scriptname`= 'boss_morchok'  WHERE `entry`= 55265;
DELETE FROM `creature_text` WHERE `entry`= 55265;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(55265, 1, 0, 'No mortal shall turn me from my task.', 14, 0, 100, 0, 0, 26282, 'Morchok'),
(55265, 1, 1, 'Cowards. Weaklings. Come down and fight, or I will bring you down.', 14, 0, 100, 0, 0, 26270, 'Morchok'),
(55265, 1, 2, 'Wyrmrest will fall. All will be dust.', 14, 0, 100, 0, 0, 26273, 'Morchok'),
(55265, 1, 3, 'I will turn this tower to rubble, and scatter it across the wastes.', 14, 0, 100, 0, 0, 26272, 'Morchok'),

(55265, 2, 0, 'You seek to halt an avalanche. I will bury you.', 14, 0, 100, 0, 0, 26268, 'Morchok'),

(55265, 3, 0, 'I am unstoppable.', 14, 0, 100, 0, 0, 26285, 'Morchok to Morchok'),
(55265, 3, 1, 'It was inevitable.', 14, 0, 100, 0, 0, 26286, 'Morchok to Morchok'),
(55265, 3, 2, 'Ground to dust.', 14, 0, 100, 0, 0, 26287, 'Morchok to Morchok'),
(55265, 4, 0, '%s summons a resonating crystal!', 41, 0, 100, 0, 0, 0, 'Morchok'),
(55265, 5, 0, 'Flee, and die.', 14, 0, 100, 0, 0, 26283, 'Morchok'),
(55265, 5, 1, 'Run, and perish.', 14, 0, 100, 0, 0, 26284, 'Morchok'),
(55265, 6, 0, 'The stone calls...', 14, 0, 100, 0, 0, 26274, 'Morchok to Morchok'),
(55265, 6, 1, 'The rocks tremble...', 14, 0, 100, 0, 0, 26276, 'Morchok to Morchok'),
(55265, 6, 2, 'The ground shakes...', 14, 0, 100, 0, 0, 26275, 'Morchok to Morchok'),
(55265, 6, 3, 'The surface quakes...', 14, 0, 100, 0, 0, 26277, 'Morchok to Morchok'),
(55265, 7, 0, '... and the black blood of the earth consumes you.', 14, 0, 100, 0, 0, 26278, 'Morchok to Morchok'),
(55265, 7, 1, '... and there is no escape from the Old Gods.', 14, 0, 100, 0, 0, 26279, 'Morchok to Morchok'),
(55265, 7, 2, '... and the rage of the true gods follows.', 14, 0, 100, 0, 0, 26280, 'Morchok to Morchok'),
(55265, 7, 3, '... and you drown in the hate of The Master.', 14, 0, 100, 0, 0, 26281, 'Morchok to Morchok'),
(55265, 8, 0, 'Impossible. This cannot be. The tower... must... fall...', 14, 0, 100, 0, 0, 26269, 'Morchok');

UPDATE `instance_template` SET `script`= 'instance_dragonsoul' WHERE `map`= 967;
