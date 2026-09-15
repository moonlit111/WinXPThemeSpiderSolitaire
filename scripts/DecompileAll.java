import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import java.io.PrintWriter;
import java.io.File;

public class DecompileAll extends GhidraScript {
    @Override
    public void run() throws Exception {
        DecompInterface decomp = new DecompInterface();
        decomp.openProgram(currentProgram);
        
        String outPath = "decompiled_spider.c";
        String[] args = getScriptArgs();
        if (args != null && args.length > 0) {
            outPath = args[0];
        }
        File outFile = new File(outPath);
        try (PrintWriter writer = new PrintWriter(outFile)) {
            FunctionIterator iter = currentProgram.getFunctionManager().getFunctions(true);
            int count = 0;
            while (iter.hasNext() && !monitor.isCancelled()) {
                Function f = iter.next();
                writer.println("// ========================================================");
                writer.println("// Function: " + f.getName() + " at " + f.getEntryPoint());
                writer.println("// ========================================================");
                DecompileResults results = decomp.decompileFunction(f, 60, monitor);
                if (results != null && results.getDecompiledFunction() != null) {
                    writer.println(results.getDecompiledFunction().getC());
                } else {
                    writer.println("// Decompilation failed for " + f.getName());
                }
                writer.println();
                count++;
            }
            println("Decompiled " + count + " functions to " + outFile.getAbsolutePath());
        }
    }
}
