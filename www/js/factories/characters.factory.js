(function() {
    
    angular.module('sheet')
    .factory('charactersFactory', charactersFactory);
    
    ////////////////////
    
    function charactersFactory ($localstorage) {
        var result = {
            getCharactersList: _getCharacters,
            getCharacterById: _getCharacterById,
            createNewCharacter: _createCharacter,
            saveCharacter: _saveCharacter,
            deleteCharacter: _deleteCharacter,
            getModifier: _getMod,
            generateUID: generateUID
        };
        
        return result;
        
        function _getCharacters () {
            return $localstorage.getObject("characters");
        }
        
        function _getCharacterById (uid) {
            var characters = _getCharacters();
            if(characters) {
                return characters[uid];
            }
        }
        
        function _createCharacter (config) {
            var uid = generateUID();
            var characters = _getCharacters();
            config.uid = uid;
            characters[uid] = config;
            characters.user = "1";
            $localstorage.setObject('characters', characters);
            return characters[uid];
        }
        
        function _saveCharacter (characterObj) {
            var characters = _getCharacters();
            
            if(typeof characters[characterObj.uid] !== 'undefined') {
                characters[characterObj.uid] = characterObj;
                $localstorage.setObject('characters', characters);
            }
        }
        
        function _deleteCharacter(uid) {
            var characters = _getCharacters();
            delete characters[uid];
            $localstorage.setObject('characters', characters);
        }
        
        function _getMod (score) {
            var scoreInt = parseInt(score);
            return Math.floor((scoreInt - 10) / 2);
        }
        
        ///////////////////////////////
        // HELPER FUNCTIONS
        //////////////////////////////
        
        function generateUID () {
            return 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function(c) {var r = Math.random()*16|0,v=c=='x'?r:r&0x3|0x8;return v.toString(16);});
        }
    }
})();