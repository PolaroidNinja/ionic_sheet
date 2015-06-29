(function() {
    angular.module('ionic.utils', [])

    .factory('$localstorage', ['$window', function($window) {
        return {
            set: function(key, stat) {
                $window.localStorage[key] = stat;
            },
            get: function(key, defaultstat) {
                return $window.localStorage[key] || defaultstat;
            },
            setObject: function(key, stat) {
                $window.localStorage[key] = JSON.stringify(stat);
            },
            getObject: function(key) {
                return JSON.parse($window.localStorage[key] || '{}');
            }
        }
    }]);

})();