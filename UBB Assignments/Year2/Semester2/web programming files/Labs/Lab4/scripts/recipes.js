$(document).ready(function() {
    var window = null;

    $('#nutri_info').click(function() {
        if (!window) {
            window = $('#info').dialog({
                autoOpen: false,
                modal: true,
                resizable: true,
                draggable: false,
                height: 400,
                width: 500,
                buttons: {
                    'Close': function() {
                        window.dialog('close');
                    }
                },
                close: function() {
                    $(this).dialog('destroy');
                    window = null;
                }
            });
        }
        window.dialog('open')
    });

});