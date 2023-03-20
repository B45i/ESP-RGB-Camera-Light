<script>
    let red = 0;
    let green = 0;
    let blue = 0;
    let brightens = 50;

    async function updateData(data) {
        return fetch('rest/update', {
            method: 'POST',
            headers: {
                'content-type': 'application/json',
            },
            body: JSON.stringify(data),
        });
    }

    async function handleSave() {
        try {
            updateData({
                red,
                green,
                blue,
                brightnes: brightens,
            });
        } catch (error) {
            console.error(error);
        }
    }

    $: rgb = `rgb(${red}, ${green}, ${blue})`;
</script>

<nav class="navbar">
    <h2>LED Controller</h2>
</nav>

<main class="main">
    <div class="color-range-picker">
        <label for="range-red">Red</label>
        <input
            type="range"
            name="range-red"
            id="range-red"
            bind:value={red}
            min="0"
            max="256"
            step="1"
        />
    </div>
    <div class="color-range-picker">
        <label for="range-green">Green</label>
        <input
            type="range"
            name="range-green"
            id="range-green"
            bind:value={green}
            min="0"
            max="256"
            step="1"
        />
    </div>
    <div class="color-range-picker">
        <label for="range-blue">Blue</label>
        <input
            type="range"
            name="range-blue"
            id="range-blue"
            bind:value={blue}
            min="0"
            max="256"
            step="1"
        />
    </div>

    <div class="color-range-picker">
        <label for="range-brightnes">Brightens</label>
        <input
            type="range"
            name="range-brightnes"
            id="range-brightnes"
            bind:value={brightens}
            min="0"
            max="100"
            step="1"
        />
    </div>

    <button on:click={handleSave} class="btn" style="background-color: {rgb}"
        >Save</button
    >
</main>

<style>
    .main {
        padding: 1rem;
        display: flex;
        flex-direction: column;
        gap: 1rem;
        margin: auto;
        max-width: 30rem;
        width: 100%;
    }

    .navbar {
        padding: 1rem;
        border-bottom: 1px solid #000;
        box-shadow: rgb(0 0 0 / 15%) 0px 6px 11px 0px;
        text-align: center;
    }

    .color-range-picker {
        display: flex;
        flex-direction: column;
        gap: 0.5rem;
        padding: 1rem;
        border-radius: 6px;
        box-shadow: rgb(0 0 0 / 68%) 3px 3px 7px;
    }

    #range-red {
        accent-color: indianred;
    }

    #range-green {
        accent-color: mediumseagreen;
    }

    #range-blue {
        accent-color: royalblue;
    }

    #range-brightnes {
        accent-color: gold;
    }
</style>
