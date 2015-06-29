(function() {

    angular.module('gaming.utils', [])
        .factory('diceRoller', diceRoller);

    //////////////////////////////

    function diceRoller() {
        return {
            roll: _roll
        }

        function _roll(expression) {
            var rollRegex = /([0-9]{1,10})[d|D]([0-9]{1,10})/g;
            var matches;
            while ((matches = rollRegex.exec(expression)) !== null) {
                if (matches.index === rollRegex.lastIndex) {
                    console.log(rollRegex.lastIndex);
                    rollRegex.lastIndex++;
                }
            }
            console.log(matches);
        }
    }
})();