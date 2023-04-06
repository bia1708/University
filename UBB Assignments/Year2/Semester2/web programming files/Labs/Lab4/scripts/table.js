if (typeof window !== 'undefined') {
    document.getElementById("th0").addEventListener("click", function() { sortTable(0); });
    document.getElementById("th1").addEventListener("click", function() { sortTable(1); });
    document.getElementById("th2").addEventListener("click", function() { sortTable(2); });


    function sortTable(n) {
        var table, rows, switching, i, x, y, shouldSwitch, direction, switchcount = 0;
        table = document.getElementById("info_table");
        switching = true;

        direction = "asc";

        while (switching) {
            switching = false;
            rows = table.rows;

            // first row = headers so we can skip it
            for (i = 1; i < (rows.length - 1); i++) {
                shouldSwitch = false;
                x = rows[i].getElementsByTagName("TD")[n];
                y = rows[i + 1].getElementsByTagName("TD")[n];

                if (direction == "asc") {
                    if (x.innerHTML.toLowerCase() > y.innerHTML.toLowerCase()) {
                        shouldSwitch = true;
                        break;
                    }
                } else if (direction == "desc") {
                    if (x.innerHTML.toLowerCase() < y.innerHTML.toLowerCase()) {
                        shouldSwitch = true;
                        break;
                    }
                }
            }

            if (shouldSwitch) {
                rows[i].parentNode.insertBefore(rows[i + 1], rows[i]);
                switching = true;
                // Each time a switch is done, increase this count by 1:
                switchcount++;
            } else {
                /* If no switching has been done AND the direction is "asc",
                set the direction to "desc" and run the while loop again. */
                if (switchcount == 0 && direction == "asc") {
                    direction = "desc";
                    switching = true;
                }
            }
        }
    }
}