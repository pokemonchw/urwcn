// Evaluated by the existing Proton Wine Mono C# shell with -r:System.Core -e.
// The resident's existing protocol owns retirement, publication and loading.
new System.Action(delegate {
    var processId = System.Environment.GetEnvironmentVariable("UWCN_WINE_CONTROL_PID");
    var command = System.Text.Encoding.UTF8.GetString(System.Convert.FromBase64String(
        System.Environment.GetEnvironmentVariable("UWCN_WINE_CONTROL_COMMAND")));
    var encoding = new System.Text.UTF8Encoding(false);
    using (var pipe = new System.IO.Pipes.NamedPipeClientStream(".", "uwcn-" + processId,
            System.IO.Pipes.PipeDirection.InOut)) {
        pipe.Connect(15000);
        var bytes = encoding.GetBytes(command + "\n");
        pipe.Write(bytes, 0, bytes.Length);
        pipe.Flush();
        using (var reader = new System.IO.StreamReader(pipe, encoding, false, 4096, true)) {
            var response = reader.ReadLine();
            System.Console.WriteLine("UWCN_CONTROL_RECEIPT " + response);
        }
    }
})();
